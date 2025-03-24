/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:17:11 by fcoullou          #+#    #+#             */
/*   Updated: 2025/03/24 16:59:27 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe_class.hpp"

//	CANONICAL FORM		////////////////////////////////////////////////////////
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	*this = copy;
}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &copy)
{
    if (this != &copy)
    {
        _myVector = copy._myVector;
        _myList = copy._myList;
    }
	return *this;
}

//  CONSTRUCTOR     ////////////////////////////////////////////////////////////
PmergeMe::PmergeMe(int ac, char **av) : _size(ac - 1)
{
    parseInput(av);

    printBefore();
    
    double  tvbeg = getTime();
    mergeInsertVector();

    double  tlbeg = getTime();
    mergeInsertList();

    printAfter();
    printVLTime(tvbeg, tlbeg);
}

//  MEMBER FUNCTIONS    ////////////////////////////////////////////////////////
void    PmergeMe::parseInput(char **av)
{
    _myVector = parseVector(av);
    parseList(av);
}

vec_uint    PmergeMe::parseVector(char **av)
{
    vec_uint   vec;
    
    for (int i = 1; i < _size; ++i)
    {
        str arg = av[i];
        int val = atoi(arg.c_str());
        if (val <= 0)
            throw InvalidInteger();
        vec.push_back(val);
    }
    
    return vec;
}

list_uint    PmergeMe::parseList(char **av)
{
    
}

void    PmergeMe::mergeInsertVector()
{
    
}

void    PmergeMe::mergeInsertList()
{
    
}

void    PmergeMe::printBefore()
{
    
}

void    PmergeMe::printAfter()
{
    
}

void    PmergeMe::printVLTime(double tvbeg, double tlbeg)
{
    
}

double	PmergeMe::getTime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

//  EXCEPTIONS		    ////////////////////////////////////////////////////////
const char* PmergeMe::WrongInput::what() const throw()
{
	return (RED " [Error]" ITALIC " " RESET);
}

const char* PmergeMe::InvalidInteger::what() const throw()
{
	return (RED " [Error]" ITALIC " Only Positive Integers please" RESET);
}






// merge-insert(V) :

// V =  3 2 5 8 7 4 6 1 9

// S = 3 8 7 6                  (plus grands elements)
// P = 2 5 4 1 9                (plus petits elements + celui tout seul)

// -> S' = merge-insert(S)
// S' = 3 6 7 8
// P' = 2 1 4 5


// Suite de Jacobsthal a utiliser : 0 1 3
// V' = 2 3 6 7 8               (insere l'element associe a 3 en premier)
// V' = 1 2 3 6 7 8             (insere l'element associe a 6 en dessous du 6 (3 positions possibles))
// V' = 1 2 3 5 6 7 8           (insere l'element associe a 8 en dessous du 8 (7 positions possibles))
// V' = 1 2 3 4 5 6 7 8         (insere l'element associe a 7 en dessous du 7 (7 positions possibles))
// V' = 1 2 3 4 5 6 7 8 9       (insere l'element tout seul dans la liste entiere (10 positions possibles)

// -> V' est trie

