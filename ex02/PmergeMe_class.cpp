/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:17:11 by fcoullou          #+#    #+#             */
/*   Updated: 2025/03/28 16:20:35 by fcoullou         ###   ########.fr       */
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
PmergeMe::PmergeMe(int ac, char **av) : _size(ac)
{
    parseInput(av);

    printBefore();
    
    mergeInsertVector();

    mergeInsertList();

    printAfter();
    printVLTime(_tVec, _tList);
}

//  MEMBER FUNCTIONS    ////////////////////////////////////////////////////////
void    PmergeMe::parseInput(char **av)
{
    parseVector(av);
    parseList();
}

void    PmergeMe::parseVector(char **av)
{
    vec_uint   vec;
    
    for (int i = 1; i < _size; ++i)
    {
        str arg = av[i];
        int val = atoi(arg.c_str());
        if (val < 0)
            throw InvalidInteger();
        vec.push_back(val);
    }
    
    getVectorRef() = vec;
}

//  je construis une liste en iterant du premier de mon vecteur au dernier
void    PmergeMe::parseList()
{
    list_uint   list(_myVector.begin(), _myVector.end());

    getListRef() = list;
}

void    PmergeMe::mergeInsertVector()
{
    _tVec = std::clock();

    if (!isVectorSorted(getVectorRef()))
    {
        sortPairs(getVectorRef());
    }

    _tVec = (std::clock() - _tVec);
}

void    PmergeMe::mergeInsertList()
{
    _tList = std::clock();

    if (!isListSorted(getListRef()))
    {
        sortPairs(getListRef());
    }

    _tList = (std::clock() - _tList);
}

//  Fonction recursive qui trie les elements du vecteur en les comparant 2 a 2
// !! ATTENTION !! = Mal de crane assure : Je sais c'est pas beau, mais c'est pour comprendre
void    PmergeMe::sortPairs(vec_uint &vec)
{
    if (vec.size() == 1)                        //  Condition d'arret de la recursion
        return;

    vec_uint large, small;                      //  Division en 2 vecteurs   

    for (size_t i = 0; i < vec.size(); i += 2)  //  Je me deplace de 2 en 2 dans le vecteur
    {
        if (i + 1 < vec.size())                 //  Si je ne suis pas a la fin du vecteur
        {
            if (vec[i] > vec[i + 1])            //  Si le premier element est plus grand que le second
            {
                large.push_back(vec[i]);        //  Je les ajoute dans l'ordre inverse
                small.push_back(vec[i + 1]);
            }
            else
            {
                large.push_back(vec[i + 1]);    //  Sinon je les ajoute dans l'ordre
                small.push_back(vec[i]);
            }
        }
        else
        {
            small.push_back(vec[i]);            //  Si je suis a la fin du vecteur, j'ajoute le dernier element dans le vecteur des plus petits
        }
    }

    sortPairs(large);                           //  Recursion sur le vecteur des plus grands elements

    for (size_t i = 0; i < small.size(); ++i)   //  Je reinsere les elements du vecteur des plus petits dans le vecteur des plus grands intelligemment grace a insertSorted()
    {
        insertSorted(large, small[i]);
    }

    vec = large;                                //  Je remplace le vecteur initial par le vecteur trie
}

void    PmergeMe::sortPairs(list_uint &list)
{
    if (list.size() <= 1)                                           // Condition d'arrêt

    return;

    list_uint large, small;

    for (list_uint::iterator it = list.begin(); it != list.end();)  // On parcourt la liste deux par deux avec des itérateurs
    {
        list_uint::iterator next = it;
        ++next;                                                     // Se déplace vers l'élément suivant

        if (next != list.end())                                     // Vérifie qu'il y a bien un second élément
        {
            if (*it > *next)
            {
                large.push_back(*it);
                small.push_back(*next);
            }
            else
            {
                large.push_back(*next);
                small.push_back(*it);
            }
            it = ++next;                                            // Avance de deux
        }
        else
        {
            small.push_back(*it);
            ++it;
        }
    }

    sortPairs(large);                                               // Tri récursif de la partie "large"

    for (list_uint::iterator it = small.begin(); it != small.end(); ++it)    // Réinsertion intelligente des petits dans large
    {
        insertSorted(large, *it);
    }

    list = large;                                                   // On remplace la liste d'origine par la nouvelle triée

}

void    PmergeMe::insertSorted(vec_uint &sortedVec, uint val)
{
    // Trouve la position où insérer "val" en gardant sortedVec trié -> MAGIC
    vec_uint::iterator pos = std::lower_bound(sortedVec.begin(), sortedVec.end(), val);
    sortedVec.insert(pos, val);
}

void    PmergeMe::insertSorted(list_uint &sortedList, uint val)
{
    for (std::list<unsigned int>::iterator it = sortedList.begin(); it != sortedList.end(); ++it)
    {
        if (*it >= val)
        {
            sortedList.insert(it, val);
            return;
        }
    }
    sortedList.push_back(val); // Si on arrive à la fin, on ajoute à la fin
}

void    PmergeMe::printBefore()
{
    std::cout << std::endl;
    std::cout << CYAN << "╔═════ " BOLD "Before" << RESET << std::endl;
    std::cout << CYAN << "╚═ ";
    std::for_each(_myVector.begin(), _myVector.end(), PrintElement());
    std::cout << RESET << std::endl;
}

void    PmergeMe::printAfter()
{
    std::cout << std::endl;
    std::cout << GREEN << "╔═══════ " BOLD "After" << RESET << std::endl;
    std::cout << GREEN << "╠═ " RESET BOLD ITALIC "vector : " RESET GREEN;
    std::for_each(_myVector.begin(), _myVector.end(), PrintElement());
    std::cout << std::endl << GREEN << "╚═ " RESET BOLD ITALIC "list   : " RESET GREEN;
    std::for_each(_myList.begin(), _myList.end(), PrintElement());    
    std::cout << RESET << std::endl;
}

void    PmergeMe::printLargeAndSmall(vec_uint &large, vec_uint &small, int i)
{
    std::cout << std::endl;
    std::cout << YELLOW << "╔══════ " BOLD "Iteration : " << RESET << i << std::endl;
    std::cout << YELLOW << "╠═ " RESET BOLD ITALIC "Large : " RESET YELLOW;
    std::for_each(large.begin(), large.end(), PrintElement());
    std::cout << std::endl << YELLOW << "╚═ " RESET BOLD ITALIC "Small : " RESET YELLOW;
    std::for_each(small.begin(), small.end(), PrintElement());
    std::cout << RESET << std::endl;
}

void    PmergeMe::printVLTime(double tvec, double tlist)
{
    std::cout << std::endl;
    std::cout << MAGENTA << "╔═════════ " BOLD "Sorting" << RESET << std::endl;
    std::cout << MAGENTA "╠═ " RESET BOLD << _size - 1 << RESET ITALIC " elements in a " BOLD "vector :  " RESET << MAGENTA << tvec << RESET ITALIC " µs" RESET << std::endl;
    std::cout << MAGENTA "╚═ " RESET BOLD << _size - 1 << RESET ITALIC " elements in a " BOLD "list   :  " RESET << MAGENTA << tlist << RESET ITALIC " µs" RESET << std::endl;
    std::cout << std::endl;
}

bool    PmergeMe::isVectorSorted(vec_uint &vec)
{
    vec_uint::iterator it = vec.begin();
    vec_uint::iterator ite = vec.end();
    vec_uint::iterator itn = it + 1;

    while (itn != ite)
    {
        if (*it > *itn)
            return false;
        ++it;
        ++itn;
    }
    return true;
}

bool    PmergeMe::isListSorted(list_uint &list)
{
    list_uint::iterator it = list.begin();
    list_uint::iterator ite = list.end();
    list_uint::iterator itn = it;
    ++itn;

    while (itn != ite)
    {
        if (*it > *itn)
            return false;
        ++it;
        ++itn;
    }
    return true;
}

//  GETTERS			    ////////////////////////////////////////////////////////
vec_uint    PmergeMe::getVector() const
{
    return _myVector;
}

vec_uint    &PmergeMe::getVectorRef()
{
    return _myVector;
}

list_uint    PmergeMe::getList() const
{
    return _myList;
}

list_uint    &PmergeMe::getListRef()
{
    return _myList;
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

//  EXCEPTIONS		    ////////////////////////////////////////////////////////
struct PrintElement
{
    void operator()(const unsigned int& elem) const
    {
        std::cout << elem << " ";
    }
};



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

