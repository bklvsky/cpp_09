/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:06:31 by dselmy            #+#    #+#             */
/*   Updated: 2023/05/21 17:45:09 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*
int checkArguments (const std::ifstream & db, const std::ifstream & input)
{
	if (db.is_open() && db.good())
	{
		if (input.is_open() && input.good())
			return 0;
		std::cout << "Error: could not open the [input] file." << std::endl;
	}
	else
	{
		std::cout << "Error: could not open the database." << std::endl << 
		"Make sure that there is a [data.csv] file in the same directory" << std::endl;
	}
	return -1;
}
*/

int main (int argc, char ** argv)
{
	
	if (argc != 2)
	{
		std::cout << "Usage:" << std::endl;
		std::cout << "./btc [name of the .txt file] to analyze" << std::endl;
		return 1;
	}
	
	try 
	{
		BitcoinExchange exchanger;
		exchanger.calculate(argv[1]);
	} 
	catch (std::exception & e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}
