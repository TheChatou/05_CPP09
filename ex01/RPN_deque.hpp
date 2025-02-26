/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN_deque.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:12:13 by fcoullou          #+#    #+#             */
/*   Updated: 2025/02/26 13:06:59 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <deque>

//	Some Colors	--------------------------------------------------------------
#define RESET	"\033[0m"
#define BLUE	"\033[34m"
#define CYAN	"\033[36m"
#define YELLOW	"\033[33m"
#define GREEN	"\033[32m"
#define RED		"\033[31m"
#define MAGENTA "\033[35m"
#define GRAY    "\033[37m"
#define ITALIC  "\033[3m"
#define BOLD	"\033[1m"
#define UNDERLINED  "\033[4m"

class RPN
{
    private :
        std::deque<char>     _myDeque;

    public :
        RPN();
        RPN(const RPN &copy);
        ~RPN();
        RPN &operator=(const RPN &copy);

        std::deque<char>    getMyDeque() const;
        std::deque<char>    &getMyDequeRef();

        void                execRPN();
        float               calc(float x, float y, char op);

        bool                notDigitOrOp(int c);

    //  EXCEPTIONS		    ////////////////////////////////////////////////////////
		class WrongOperator: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

};