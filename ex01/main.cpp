/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:48:35 by dselmy            #+#    #+#             */
/*   Updated: 2023/05/25 17:54:19 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include "./RPN.hpp"

int main (int argc, char ** argv)
{
	if (argc < 2) {
		std::cout << "Usage: ./RPN [an RPN expression to calulate]" << std::endl;
		std::cout << "Example: ./RPN \"8 9 * 9 - 9 - 9 - 4 - 1 +\"" << std::endl;
		return 1;
	}
	RPN calculator;
	std::string token;
	for (int i = 1; i < argc; i++) {
		std::stringstream stream (argv[i]);
		while (true) {
			std::string token = "";
			stream >> token;
			if (token.empty())
				break;
			if (token.length() > 1) {
				std::cout << "Error: wrong format of argument [" << token << "]" << std::endl;
				std::cout << "Allowed symbols: 123456789+-*/ delimeted by a whitespace" << std::endl;
				return -1;
			}
			std::cout << "token: [" << token << "]" << std::endl;
			if (calculator.add(token) < 0)
				return -1;
		}
	}
	
	if (calculator.size() != 1) {
		std::cout << "Error: could not complete the calculation" << std::endl;
		return 1;
	}
	std::cout << calculator.front() << std::endl;
	return 0;
}
