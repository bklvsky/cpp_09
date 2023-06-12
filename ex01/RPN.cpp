/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:49:50 by dselmy            #+#    #+#             */
/*   Updated: 2023/05/31 17:22:28 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./RPN.hpp"

RPN::RPN(): myDeque() {}

RPN::RPN(const RPN & rhs) {
	*this = rhs;
}

RPN & RPN::operator= (const RPN & rhs)
{
	myDeque = rhs.myDeque;
	return *this;
}

RPN::~RPN() {}

int sum(int first, int second) {
	if (first > 0 && second > 0 && (first > INT_MAX - second))
		throw std::overflow_error("Integer overflow in sum");
	if (first < 0 && second < 0 && (first < INT_MIN + second))
		throw std::underflow_error("Integer underflow in sum");
	return first + second;
}

int substraction(int first, int second) {
	if (first < 0 && second > 0 && (first < INT_MIN + second))
		throw std::underflow_error("Integer underflow in substraction");
	else if (first > 0 && second < 0 && (first > INT_MAX + second))
		throw std::overflow_error("Integer overflow in substraction");
	return first - second;
}

int division(int first, int second) {
	if (second == -1 && first == INT_MIN)
		throw std::overflow_error("Integer overflow in division");
	if (second == 0)
		throw std::runtime_error("Zero division");
	return first / second;
}

int multiplication(int first, int second) {
	if ((first == -1 && second == INT_MIN ) ||
		(first == INT_MIN && second == -1))
		throw std::overflow_error("Integer overflow in multiplication");
	if (first == 0 && second == 0)
		return 0;
	if ((first > 0 && second > 0 && (first > INT_MAX / second)) ||
		(first < 0 && second < 0 && (first < INT_MAX / second)))
		throw std::overflow_error("Integer overflow in multiplication");
	if ((first < 0 && second > 0 && first < (INT_MIN / second) )|| 
		(first > 0 && second < 0 && first > (INT_MIN / second)))
		throw std::underflow_error("Integer underflow in multiplication");
	return first * second;
}

void	RPN::calculate(char operation) {
	if (myDeque.size() < 2) {
		std::string errMessage;
		errMessage = std::string("Wrong format - not enough numbers to execute ") + operation + std::string(" operation.");
		throw std::runtime_error(errMessage);
	}

	int first, second, result;
	
	second = myDeque.front();
	myDeque.pop_front();
	first = myDeque.front();
	myDeque.pop_front();
	
	switch (operation) {
		case '-': result = substraction(first, second); break;
		case '+': result = sum(first, second); break;
		case '/': result = division(first, second); break;
		default: result = multiplication(first, second); break;
	}
	myDeque.push_front(result);
}

int RPN::add (std::string arg) {
	if (arg.find_first_of("123456789") != std::string::npos) {
		myDeque.push_front(arg[0] - '0');
	} else if (arg.find_first_of("-+/*") != std::string::npos) {
		try {
			calculate(arg[0]);
		} catch (std::runtime_error & e) {
			std::cout << "Error: " << e.what() << std::endl;
			return -1;
		}
	} else {
		std::cout << "Error: unknown symbol" << std::endl;
		return -1;
	}
	return 0;
}

size_t RPN::size() const {
	return myDeque.size();
}

int RPN::front() const {
	return myDeque.front();
}
