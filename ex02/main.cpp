/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:21:06 by dselmy            #+#    #+#             */
/*   Updated: 2023/06/20 18:06:12 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <exception>
#include <cerrno>

static void putWrongFormat(std::string token) {
	std::cout << "Error: wrong format of argument [" << token << "]" << std::endl;
	std::cout << "Expected a sequence of positive numbers to sort." << std::endl;
}

static int checkArguments(int argc, char ** argv) {
	std::string token;
	errno = 0;
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
			if ((token.size() == 10 && token.compare("2147483647") > 0) || token.size() > 10) {
				std::cout << "Error: too large a number: " 
													<< token << ". " << std::endl;
				return -1;
			}
			int res = atoi(token.c_str());
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
	// PmergeMe < std::list<int>, std::list<std::list <int> > > sorterLst;
	// sorterLst.sort(argc, argv);

	// PmergeMe < std::vector<int>, std::vector <std::vector<int> > > sorterVct;
	// sorterVct.sort(argc, argv);
	
	// try {
	// } catch (std::exception & e) {
	// 	std::cout << "Error: " << e.what() << std::endl;
	// 	return 1;
	// }
}
