/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:50:01 by dselmy            #+#    #+#             */
/*   Updated: 2023/05/25 17:53:26 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <limits.h>
#include <string>
#include <deque>
#include <stack>

class RPN {

	private:
	std::deque<int> myDeque;
	
	void	calculate(char operation);

	public:
	RPN();
	RPN(const RPN & rhs);
	~RPN();
	RPN & operator= (const RPN & rhs);
	
	int		add(std::string arg);
	size_t	size() const;
	int		front() const;
};

#endif
