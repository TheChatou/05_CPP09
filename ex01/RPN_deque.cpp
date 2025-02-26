/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN_deque.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:37:01 by fcoullou          #+#    #+#             */
/*   Updated: 2025/02/26 13:07:38 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN_deque.hpp"

typedef std::deque<char>::reverse_iterator rev_it;

//	CANONICAL FORM		////////////////////////////////////////////////////////
RPN::RPN() {}

RPN::RPN(const RPN &copy)
{
	*this = copy;
}

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &copy)
{
	if (this != &copy)
	{
		this->_myDeque = copy._myDeque;
	}
	return *this;
}

//  GETTERS			    ////////////////////////////////////////////////////////
std::deque<char>     RPN::getMyDeque() const
{
    return _myDeque;
}

std::deque<char>     &RPN::getMyDequeRef()
{
    return _myDeque;
}

//  MEMBER FUNCTIONS    ////////////////////////////////////////////////////////
void				RPN::execRPN()
{
	float	x = 0;
	float	y = 0;
	char	op = 0;
	bool	x_flag = false;
	bool	y_flag = false;
	
	for (rev_it rit = _myDeque.rbegin(); rit != _myDeque.rend(); ++rit)
	{
		if (!x_flag)
		{
			x = *rit - 48;
			x_flag = true;
		}
		else if (!y_flag && x_flag)
		{
			y = *rit - 48;
			y_flag = true;
		}
		else if (op == 0 && x_flag && y_flag)
		{
			op = *rit;
			try
			{
				x = calc(x, y, op);
				y = 0;
				op = 0;
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		
		
	}
	std::cout << "RES is : " << x << std::endl;
}

float				RPN::calc(float x, float y, char op)
{
	if (op == '+')
		return x + y;
		
	if (op == '-')
		return x - y;

	if (op == '/')
		return x / y;
		
	if (op == '*')
		return x * y;

	if (op != '+' || op != '-' || op != '/' || op != '*')
		throw WrongOperator();

	return 0;
}

//  UTILS			    ////////////////////////////////////////////////////////
bool    RPN::notDigitOrOp(int c)
{
    if ((c >= '0' && c <= '9') ||
        c == '+' || c == '-' || c == '/' || c == '*')
        return false;
    return true;
}

//  EXCEPTIONS		    ////////////////////////////////////////////////////////
const char* RPN::WrongOperator::what() const throw()
{
	return (RED " [Error]" ITALIC " Valid operators only : " RESET "'+', '-', '/' & '*'");
}
