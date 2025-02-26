/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:12:13 by fcoullou          #+#    #+#             */
/*   Updated: 2025/02/26 15:29:15 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <stack>

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
        std::stack<float>     _myStack;

    public :
//	CANONICAL FORM		////////////////////////////////////////////////////////
        RPN();
        RPN(const RPN &copy);
        ~RPN();
        RPN &operator=(const RPN &copy);

//  GETTERS			    ////////////////////////////////////////////////////////
        std::stack<float>    getMyStack() const;
        std::stack<float>    &getMyStackRef();

        void                parseAndExec(char *input);
        void                stackAndCalc(char op);
        float               calc(float x, float y, char op);

        bool                notDigitOrOp(char *in);
        bool                isOperand(char c);
        bool                onlySpacesLeft(char *str);
        float               getTopThenPop();
        
//  EXCEPTIONS		    ////////////////////////////////////////////////////////
    class WrongInput: public std::exception
    {
        public:
            virtual const char* what() const throw();
    };

    class WrongInputSpaces: public std::exception
    {
        public:
            virtual const char* what() const throw();
    };

    class NotEnoughElements: public std::exception
    {
        public:
            virtual const char* what() const throw();
    };

    class WeirdLastDigits: public std::exception
    {
        public:
            virtual const char* what() const throw();
    };

};