/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:17:44 by fcoullou          #+#    #+#             */
/*   Updated: 2025/03/28 16:18:28 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <algorithm>
#include <iomanip>

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

        std::clock_t    _tVec;
        std::clock_t    _tList;

        int             _size;

        struct PrintElement
        {
            void operator()(const unsigned int& elem) const
            {
                std::cout << elem << " ";
            }
        };
                
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
        void            parseVector(char **av);
        void            parseList();

        void            mergeInsertVector();
        void            mergeInsertList();
        void            sortPairs(vec_uint &vec);
        void            sortPairs(list_uint &list);
        void            insertSorted(vec_uint &sortedVec, uint val);
        void            insertSorted(list_uint &sortedList, uint val);
        
        void            printBefore();
        void            printAfter();
        void            printLargeAndSmall(vec_uint &large, vec_uint &small, int i);
        void            printVLTime(double tvbeg, double tlbeg);

        bool            isVectorSorted(vec_uint &vec);
        bool            isListSorted(list_uint &list);

        //  GETTERS			    ////////////////////////////////////////////////////////
        vec_uint        getVector() const;
        vec_uint        &getVectorRef();
        list_uint       getList() const;
        list_uint       &getListRef();

        
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