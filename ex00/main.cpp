/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:17:02 by fcoullou          #+#    #+#             */
/*   Updated: 2025/04/01 15:05:01 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

#define	DATABASE	true
#define INPUT		false
#define	DATA_CSV	"data.csv"

int	creatingInputBase(char *input, BtcMap &myData)
{
	std::ifstream	is(input);
	if (!is.is_open())
	{
		std::cerr << RED "[Error] Sorry I can't open the Input file" RESET << std::endl;
		return 1;
	}

	myData.welcome();
	myData.printTab();
	std::string		line;
	if (std::getline(is, line))
	{
		if (line != "date | value")
		{
			std::cerr << BOLD RED " - Wrong Input format -" RESET << std::endl;
			std::cerr << RED "1st line should be : " RESET << "\t\t\"date | value\"" << std::endl;
			std::cerr << RED "Then, the format should be : " RESET << "\t\"YYYY-MM-DD | (float value between 0 and 1000)\"" << std::endl;
			return 1;
		}
	}
	
	while (getline(is, line))
	{
		if (is.fail())
		{
			std::cerr << RED "[Error] dataBase File Reading Error" RESET << std::endl;
			break;
		}
		else if (line == "" || line == "date | value")
		{
			continue;
		}
		else if (myData.parse(line, INPUT))
			return 1;		
	}
	
	return 0;
}

// ifstream(const char* __s, ios_base::openmode) ------ > constructeur qui init() et open()
// Si pas de second parametre, mode par defaut
int	creatingDataBase(BtcMap &myData)
{
	std::cout << std::endl << ITALIC GRAY "           ---  Welcome to the BitcoinExchanger Program --- " RESET << std::endl << std::endl;
	
	std::ifstream	is(DATA_CSV);
	if (!is.is_open())
	{
		std::cerr << RED "[Error] Sorry I can't open the dataBase" RESET << std::endl;
		return 1;
	}
	
//	Je saute la premiere ligne	
	std::string		line;
	if (std::getline(is, line) && line == "date,exchange_rate") {}
	
	while (getline(is, line))
	{
		if (is.fail())
		{
			std::cerr << RED "[Error] dataBase File Reading Error" RESET << std::endl;
			break;
		}
		else if (myData.parse(line, DATABASE))
			return 1;		
	}

	is.close();
	return 0;
}


//	MAIN		////////////////////////////////////////////////////////////////////
//	creatingDataBase() parse et insert les donnees du fichier data.csv dans la map
//	creatingInputBase() parse l'Input donne en argument et calcule le montant en fonction de la date
// si tout se passe bien, on affiche le resultat et on quitte le programme
int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << RED "[Error] You need a file to run this program." RESET << std::endl;
		return 1;
	}

	BtcMap			myData;
	if (creatingDataBase(myData) || creatingInputBase(av[1], myData))
	{
		return 1;
	}
		
	myData.goodbye();
	return 0;
}