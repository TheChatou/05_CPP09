/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:17:44 by fcoullou          #+#    #+#             */
/*   Updated: 2025/03/24 17:00:27 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <sys/time.h>

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

//  Some Macros --------------------------------------------------------------
typedef unsigned int        uint;
typedef std::vector<uint>   vec_uint;
typedef std::list<uint>     list_uint;
typedef std::string         str;

class PmergeMe
{
    private :
        vec_uint        _myVector;
        list_uint       _myList;

        int             _size;
    
    public :
        //	CANONICAL FORM		////////////////////////////////////////////////////////
        PmergeMe();
        PmergeMe(const PmergeMe &copy);
        ~PmergeMe();
        PmergeMe &operator=(const PmergeMe &copy);
    
        //  CONSTRUCTOR     ////////////////////////////////////////////////////////////
        PmergeMe(int ac, char **av);

        //  MEMBER FUNCTIONS    ////////////////////////////////////////////////////////
        void            parseInput(char **av);
        vec_uint        parseVector(char **av);
        list_uint       parseList(char **av);

        void            mergeInsertVector();
        void            mergeInsertList();

        void            printBefore();
        void            printAfter();
        void            printVLTime(double tvbeg, double tlbeg);

        double          getTime();
        
        //  EXCEPTIONS		    ////////////////////////////////////////////////////////
        class WrongInput: public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
    
        class InvalidInteger: public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
    
};