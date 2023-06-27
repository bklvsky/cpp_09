/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:06:41 by dselmy            #+#    #+#             */
/*   Updated: 2023/06/12 17:04:45 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
	parseDb();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange & rhs) {
	this->dbValues.insert(rhs.dbValues.begin(), rhs.dbValues.end());
}

BitcoinExchange & BitcoinExchange::operator= (const BitcoinExchange & rhs) {
	if (!dbValues.empty()) {
		dbValues.clear();
	}
	dbValues.insert(rhs.dbValues.begin(), rhs.dbValues.end());
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

static int isLeapYear(int year) {
	return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

static int daysInAMonth(int year, int month) {
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		return 30;
	}
	if (month == 2) {
		return 28 + isLeapYear(year);
	}
	return 31;
}

static int checkDate(int year, int month, int day) {
	if (year <= 0 || month <= 0 || day <= 0) {
		std::cout << "Error: wrong date representation" << std::endl;
	} else if (month > 12) {
		std::cout << "Error: wrong month representation" << std::endl;
	} else if (day > daysInAMonth(year, month)) {
		std::cout << "Error: wrong day representation" << std::endl;
	} else {
		return 0;
	}
	return -1;
}

static int verifyDate(std::string date) {
	int year = 0;
	int month = 0;
	int day = 0;
	std::replace(date.begin(), date.end(), '-', ' ');
	std::istringstream (date) >> year >> month >> day;

	return checkDate(year, month, day);
}

void BitcoinExchange::parseDb() {
	std::ifstream db ("data.csv");
	if (!db.is_open() || db.bad()) {
		throw (std::runtime_error("Could not open the data.csv file"));
	}
	std::string str;
	while (std::getline(db, str)) {
		if (str.compare("date,exchange_rate") == 0)
			continue;
		size_t delimPos = str.find(',');
		
		if (delimPos == str.npos) {
			std::string errMessage = "Wrong database format (no comma delimeter) at:\n" + str;
			db.close();
			throw (std::runtime_error(errMessage));
		}

		std::string date = str.substr(0, delimPos);
		
		std::string valueStr = str.substr(delimPos + 1);
		if (valueStr.find_first_not_of("-+0123456789.", 0) != std::string::npos) {
			std::string errMessage = "Wrong database format (unknown symbol) at:\n" + str;
			db.close();
			throw (std::runtime_error(errMessage));
		}

		errno = 0;
		double value = strtod(valueStr.c_str(), NULL);
		if (errno) {
			std::string errMessage =  "Double overflow while reading data.csv at:\n" + str;
			db.close();
			throw (std::runtime_error(errMessage));
		}
		
		if (value < 0) {
			std::string errMessage = "Wrong database format (negative value) at:\n" + str;
			db.close();
			throw (std::runtime_error(errMessage));
		}

		dbValues.insert(std::make_pair(date, value));
	}
	db.close();
}

void BitcoinExchange::calculate(const char * inputFile) const {
	std::ifstream input (inputFile);
	if (input.bad() || !input.is_open())
		throw (std::runtime_error("Could not open " + std::string(inputFile)));
	std::string str;
	while (std::getline(input, str) && input.good()) {
		if (str.compare("date | value") == 0 || str.empty())
			continue;
		parseInput(str);
	}
}

void BitcoinExchange::getBitcoinValue(std::string date, float value) const {
	std::map<std::string, float>::const_iterator it = dbValues.upper_bound(date);
	if (it == dbValues.begin() && it->first != date) {
		std::cerr << "Error: no data for this date." << std::endl;
		return;
	}
	--it;
	if (it->second > std::numeric_limits<double>::max() / value) {
		std::cerr << "Error: double overflow while " << 
						"calculating value for " << date << std::endl;
		return;
	}
	std::cout << date << " => " << value << " = " << value * it->second << std::endl;
}

static int checkInputFormat(std::string str, size_t delimPos) {
	if (delimPos == std::string::npos || delimPos == 0 || \
			str[delimPos + 1] != ' ' || str[delimPos - 1] != ' ')
		return -1;
	return 0;
}

static int verifyValue(double value) {
	if (value > 0.0 && value < 1000)
		return 0;
	if (value <= 0.0)
		std::cerr << "Error: not a positive number." << std::endl;
	else
		std::cerr << "Error: too large a number." << std::endl;
	return -1;
}

void BitcoinExchange::parseInput(std::string str) const {
	
	size_t delimPos = str.find('|');
	
	if (checkInputFormat(str, delimPos) < 0) {
		std::cout << "Error: bad input => " << str << std::endl;
		return;
	}
		
	std::string date = str.substr(0, delimPos - 1);

	if (verifyDate(date) < 0) {
		return;
	}

	std::string valueStr = str.substr(delimPos + 2);
	
	if (valueStr.find_first_not_of("01234567890-+.") != std::string::npos) {
		std::cerr << "Error: bad value format => [" << valueStr << "]" << std::endl;
		return;
	}
	// std::cout << valueStr << std::endl;
	double value = strtod(valueStr.c_str(), NULL);
	// TBD: i should check if it is bigger than an float too
	if (verifyValue(value) < 0)
		return;

	getBitcoinValue(date, value);
}
