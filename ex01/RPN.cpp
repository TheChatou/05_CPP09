/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:37:01 by fcoullou          #+#    #+#             */
/*   Updated: 2025/02/27 14:07:31 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

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
		this->_myStack = copy._myStack;
	}
	return *this;
}

//  GETTERS			    ////////////////////////////////////////////////////////
std::stack<float>     RPN::getMyStack() const
{
    return _myStack;
}

std::stack<float>     &RPN::getMyStackRef()
{
    return _myStack;
}

//  MEMBER FUNCTIONS    ////////////////////////////////////////////////////////
void				RPN::parseAndExec(char *input)
{
	if (!notDigitOrOp(input))
		throw WrongInput();

	for (int i = 0; input[i]; i++)
	{
		if (isdigit(input[i]))
		{
			getMyStackRef().push(input[i] - 48);
			if (getMyStackRef().size() > 1 && (!input[i + 1] || onlySpacesLeft(input + i + 1)))
			{
				throw WeirdLastDigits();
			}
		}
		else if (input[i] == ' ')
		{
			if (input[i + 1] && input[i + 1] == ' ')
				throw WrongInputSpaces();
			continue;
		}
		else if (isOperand(input[i]))
		{
			// std::cout << " top before calc with [" << input[i] << "] : " << getMyStackRef().top() << std::endl;
			if (getMyStack().size() < 2)
				throw NotEnoughElements();

			stackAndCalc(input[i]);
		}
		else
			throw WrongInput();
	}

	std::cout << GREEN " RESULT : " RESET << getMyStack().top() << std::endl;
}

void				RPN::stackAndCalc(char op)
{
	float x = getTopThenPop();
	float y = getTopThenPop();

	getMyStackRef().push(calc(x, y, op));
	// std::cout << " top after calc : " << getMyStackRef().top() << std::endl;
}

float				RPN::calc(float x, float y, char op)
{
	if (op == '+')
	{
		// std::cout << "--> " << x << " " << op << " " << y << " = " << x + y << std::endl;  
		return x + y;
	}
	else if (op == '-')
	{
		// std::cout << "--> " << x << " " << op << " " << y << " = " << x - y << std::endl;  
		return x - y;
	}
	else if (op == '/')
	{
		// std::cout << "--> " << x << " " << op << " " << y << " = " << x / y << std::endl;  
		return x / y;
	}
	else
	{
		// std::cout << "--> " << x << " " << op << " " << y << " = " << x * y << std::endl;  
		return x * y;
	}
}

//  UTILS			    ////////////////////////////////////////////////////////
bool    RPN::notDigitOrOp(char *in)
{
    for (int i = 0; in[i]; i++)
    {
        if (i % 2 == 0 &&
			(!isdigit(in[i]) &&
			in[i] != '+' && in[i] != '-' &&
			in[i] != '/' && in[i] != '*'))
        {
			std::cout << "0 [" << in[i] << "]" << std::endl;
            return false;
        }
        else if (i % 2 == 1 && in[i] != ' ')
		{
			std::cout << "1 [" << in[i] << "]" << std::endl;
			return false;
		}
    }
    return true;
}

bool	RPN::isOperand(char c)
{
    if (c == '+' || c == '-' || c == '/' || c == '*')
		return true;
    return false;
}

bool	RPN::onlySpacesLeft(char *str)
{
	int i = 0;
	while (str[i])
	{
		// std::cout << "[" << str[i] << "]" << std::endl;
		if (str[i] != ' ')
			return false;
		i++;
	}
	return true;
}

float	RPN::getTopThenPop()
{
	float f = getMyStackRef().top();
	getMyStackRef().pop();
	return f;
}

//  EXCEPTIONS		    ////////////////////////////////////////////////////////
const char* RPN::WrongInput::what() const throw()
{
	return (RED " [Error]" ITALIC " Only Digits please, and Valid operators only : " RESET "'+', '-', '/' & '*'");
}

const char* RPN::WrongInputSpaces::what() const throw()
{
	return (RED " [Error]" ITALIC " Chill out with the space bar ! Keep the regular RPN format !" RESET);
}

const char* RPN::NotEnoughElements::what() const throw()
{
	return (RED " [Error]" ITALIC " You need at least 2 elements to do some maths" RESET);
}

const char* RPN::WeirdLastDigits::what() const throw()
{
	return (RED " [Error]" ITALIC " There's some leftover digits, and that's not conform Reverse Polish Notation .. " RESET);
}
