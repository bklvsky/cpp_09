/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:06:37 by dselmy            #+#    #+#             */
/*   Updated: 2023/05/21 17:32:02 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <time.h>

class BitcoinExchange
{
	/*
		1. constructor only takes a string input_file_name as an argument and stores it
		2. parse database -> its kinda like initial data loading, it's alright to do it in the constructor
		3. parse input -> calculation stage, not in the constructor
	*/

	/*
		1. I should make some custom exceptions;
		2. move static methods to the class but to the static-private mode
		3. my_strod to check for possible errors and throw one of the custom excepetions.
	*/
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange & rhs);
		~BitcoinExchange();
		BitcoinExchange & operator=(const BitcoinExchange & rhs);

		void calculate(const char * inputFile) const;

	private:
		std::map<std::string, float> dbValues;

		void parseDb();
		void parseInput(std::string line) const;
		void getBitcoinValue(std::string date, float value) const;
};

#endif