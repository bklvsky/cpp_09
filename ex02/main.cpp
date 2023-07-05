/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:21:06 by dselmy            #+#    #+#             */
/*   Updated: 2023/07/05 02:02:55 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>
#include <limits>

static void putWrongFormat(std::string token) {
	std::cout << "Error: wrong format of argument [" << token << "]" << std::endl;
	std::cout << "Expected a sequence of positive numbers to sort." << std::endl;
}

static std::string maxUToString()
{
	std::stringstream ss;
	ss << std::numeric_limits<unsigned>::max();
	return ss.str();
}

static int checkArguments(int argc, char ** argv) {
	std::string token;
	for (int i = 1; i < argc; i++) {
		std::stringstream stream (argv[i]);
		while (true) {
			std::string token = "";
			stream >> token;
			if (token.empty())
				break;
			if (token.find_first_not_of("0123456789") != std::string::npos) {
				putWrongFormat(token);
				return -1;
			}

			if (token.size() > 10 ||
					(token.size() == 10 && token > maxUToString()))
			{
				std::cout << "Error: too large a number: " << token << ". " << std::endl;
				return -1;
			}

			unsigned res = strtoul(token.c_str(), NULL, 10);
			if (res == 0) {
				putWrongFormat(token);
				return -1;
			}
		}
	}
	return 0;
}

int main(int argc, char ** argv) {
	if (argc < 2) {
		std::cout << "Usage: ./PmergeMe a sequence of numbers  to sort" << std::endl;
		std::cout << "Example: ./PmergeMe 3 5 9 7 4" << std::endl;
		return 1;
	}

	if (checkArguments(argc, argv) < 0)
		return 1;

	PmergeMe sorter;
	sorter.sortVct(argc, argv);
	sorter.sortLst(argc, argv);

	sorter.print();
	// sorter.checkResult();
}
