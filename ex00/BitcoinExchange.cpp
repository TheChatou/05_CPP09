/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:15:18 by fcoullou          #+#    #+#             */
/*   Updated: 2025/04/01 15:11:36 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

//	CANONICAL FORM		////////////////////////////////////////////////////////
BtcMap::BtcMap() {}

BtcMap::BtcMap(const BtcMap &copy)
{
	*this = copy;
}

BtcMap::~BtcMap() {}

BtcMap &BtcMap::operator=(const BtcMap &copy)
{
	if (this != &copy)
	{
		this->_data = copy._data;
	}
	return *this;
}

//  GETTERS			    ////////////////////////////////////////////////////////
std::map<std::string, float>	BtcMap::getDataMap() const
{
	return _data;
}

//	Getter qui renvoie l'iterateur de la map a la date la plus proche de celle passee en argument
// Si la date n'est pas dans la map, on renvoie l'iterateur du bloc precedent
// si la date est anterieure a la premiere date de la map, on renvoie l'iterateur de la premiere date
std::map<std::string, float>::iterator	BtcMap::getDateCurrency(std::string &date)
{
	std::map<std::string, float>::iterator it = _data.lower_bound(date);
	if (it == _data.end() || it->first != date)
	{
		if (it == _data.begin())
		{
			return _data.begin();
		}
		--it;
	}
	return it;

}

//  MEMBER FUNCTIONS    ////////////////////////////////////////////////////////
//	Fonction qui parse le genere le map de la database, si wichOne est true (true = database)
// Sinon, elle prend l'input et calcule le montant en fonction de la date.
// Dans chaque cas, elle renvoie le message d'erreur approprie.
int	BtcMap::parse(std::string &line, bool wichOne)
{
	try
	{
		if (wichOne)
			_data.insert(std::make_pair(this->parseDate(line), this->parseValue(line)));
		else
			howMuch(line);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

//	Je prends les 10 premiers caracteres de la ligne, je check ensuite si la date est valide
// et je la renvoie si c'est le cas
std::string	BtcMap::parseDate(std::string &line)
{
	std::string	date = line.substr(0, 10);
	checkDate(date);
	return date;
}

//	Je prends la partie de la ligne apres la virgule, je check si c'est un float valide
// et je le renvoie si c'est le cas
float	BtcMap::parseValue(std::string &line)
{
	size_t		first = line.find(',');
	if (first == std::string::npos)
	{
		throw WrongInputFormat();
	}
	
	std::string	value = line.substr(first + 1);
	if (!isFloat(value))
	{
		throw WrongValue();		
	}
	
	float		flVal;
	std::stringstream	ss(value);
	ss >> flVal;
	if (ss.fail() || flVal < 0)
	{
		throw WrongValue();		
	}
	
	return (flVal);
}

//	Verification du nombre de bitcoins entre 0 et 1000. Donc float et positif.
float	BtcMap::parseAmount(std::string &line)
{
	size_t		first = line.find(" | ");
	if (first == std::string::npos)
	{
		throw WrongInputFormat();
	}
	
	std::string	amount = line.substr(first + 3);
	if (!isFloat(amount))
	{
		throw WrongInputFormat();		
	}
	
	float		flAmount;
	std::stringstream	ss(amount);
	ss >> flAmount;
	if (ss.fail() || flAmount < 0 || flAmount > 1000)
	{
		throw WrongAmount();		
	}
	
	return (flAmount);
}

//	Verification de la date, si elle est bien formatee, si elle est valide et si elle n'est pas dans le futur,
// et si elle n'est pas une date speciale (mois de 28, 30 ou 31 jours, et les annees bisexstiles avec des 29 fevrier)
void	BtcMap::checkDate(std::string &date) const
{
	if (date.size() != 10)
	{
		throw WrongInputFormat();
	}
		
	std::string	year_str = date.substr(0, 4);
	std::string fstDash = date.substr(4, 1);
	std::string month_str = date.substr(5, 2);
	std::string secDash = date.substr(7, 1);
	std::string	day_str = date.substr(8, 2);
	
	if (!isNum(year_str) || !isNum(month_str) || !isNum(day_str) || fstDash != "-" || secDash != "-") 
	{
		throw WrongInputFormat();
	}
	
	int	year = std::atoi(year_str.c_str());
	int month = std::atoi(month_str.c_str());
	int	day = std::atoi(day_str.c_str());
	if (month < 1 || month > 12 || day < 1)
	{
		throw WrongDate();
	}
	else if (date > "2025-03-31")
	{
		throw FutureDate();
	}
	else if (specialDate(year, month, day))
	{
		throw WrongSpecialDate(year, month, day);
	}
}

//	Verification si l’année est bissextile pour valider le 29 février
//	On teste d’abord si l’année est divisible par 4, condition nécessaire
//	Mais une année divisible par 100 n’est pas bissextile, sauf si elle est aussi divisible par 400
//	Exemples : 2000 est bissextile (divisible par 400), mais 1900 ne l’est pas (divisible par 100 mais pas par 400)
bool	BtcMap::specialDate(int year, int month, int day) const
{
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return true;
	else if (month == 2) 
	{
		if (day > 29) 
			return true;
		else if (day == 29 && !(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
			return true;
	}
	return false;
}

//	Je reprends le parsing de la date pour checker et enregistrer la date, et je parse le nombre de bitcoins a calculer.
int	BtcMap::howMuch(std::string &line)
{
    std::string		date = parseDate(line);
    float			amount = parseAmount(line);

    float	res = calcBtc(date, amount);

    std::cout << "│ " << MAGENTA << std::setw(11) << std::right << getDateCurrency(date)->first << RESET
              << " │ " << CYAN  << std::setw(9)<< amount << RESET 
              << " │ " << YELLOW << std::setw(22) << getDateCurrency(date)->second << RESET
              << " │ " << BOLD GREEN << std::setw(16) << res << RESET << " │" << std::endl;

	return 0;
}

//	Calcul du montant, grace a la date qui agit comme clef pour la map, on trouve la valeur du bitcoin a cette date
// qui est multipliee par le nombre de bitcoins a convertir.
float	BtcMap::calcBtc(std::string &date, float amount)
{
	return amount * getDateCurrency(date)->second;
}

//  UTILS			    ////////////////////////////////////////////////////////
bool	BtcMap::isNum(const std::string& str) const
{
    for (size_t i = 0; i < str.length(); i++)
	{
        if (!std::isdigit(str[i]))
		{
            return false; 
        }
    }
    return true;
}

bool	BtcMap::isFloat(const std::string& str) const
{
	bool	hasPoint = false;
	
    for (size_t i = 0; i < str.length(); i++)
	{
        if (std::isdigit(str[i]))
		{
            continue; 
        }
		else if (str[i] == '.' && !hasPoint)
		{
			hasPoint = true;
		}
		else
		{
			return false;
		}
    }
    return true;
}

//	UTILS de prints
void	BtcMap::welcome() const
{
	std::cout << UNDERLINED "\tTransaction history: " RESET << std::endl; 
	std::cout << " ─────────────────────────────────────────────────────────────────────" << std::endl;
}

void	BtcMap::goodbye() const
{
	std::cout << " ─────────────────────────────────────────────────────────────────────" << std::endl;
	std::cout << ITALIC GRAY "           ---  Thank you for using BitcoinExchanger  --- " RESET << std::endl << std::endl;
}

void	BtcMap::printTab() const
{
	std::cout << "│ " << BOLD << std::setw(15) << std::right << "Date" RESET
			<< " │ " << BOLD << std::setw(13) << "Bitcoins" RESET
			<< " │ " << BOLD << std::setw(26) << "Currency on that date" RESET
			<< " │ " << BOLD << std::setw(20) << "Total amount" RESET << " │" << std::endl;
}


//  EXCEPTIONS		    ////////////////////////////////////////////////////////
const char* BtcMap::WrongDate::what() const throw()
{
	return (RED " [Error]" ITALIC " This date doesn't look right... Try again!" RESET);
}

const char* BtcMap::WrongInputFormat::what() const throw()
{
	return (RED " [Error]" ITALIC " Invalid format! Expected:" RESET " \"YYYY-MM-DD | (float value between 0 and 1000)\"" ITALIC RED " Give it another shot!" RESET);
}

const char* BtcMap::FutureDate::what() const throw()
{
	return (RED " [Error]" ITALIC " I may be good, but predicting the future? Not quite." RESET);
}


const char* BtcMap::WrongValue::what() const throw()
{
	return (RED " [Error]" ITALIC " Hmm... that value seems a bit off... check your database and try again." RESET);
}

const char* BtcMap::WrongAmount::what() const throw()
{
	return (RED " [Error]" ITALIC " Hmm... that amount looks suspicious. Please enter a float between 0 and 1000." RESET);
}

//	Exception pour les dates speciales, oui je me suis amuse a faire un message custom et precis
BtcMap::WrongSpecialDate::WrongSpecialDate(int year, int month, int day): _year(year), _month(month), _day(day)
{
	std::map<int, std::string> calendar;
		calendar[1] = "January";
		calendar[2] = "February";
		calendar[3] = "March";
		calendar[4] = "April";
		calendar[5] = "May";
		calendar[6] = "June";
		calendar[7] = "July";
		calendar[8] = "August";
		calendar[9] = "September";
		calendar[10] = "October";
		calendar[11] = "November";
		calendar[12] = "December";
		
	std::ostringstream oss;
	std::string	en = "th";
	if (day % 10 == 1 && day != 11)
		en = "st";
	else if (day % 10 == 2 && day != 12)
		en = "nd";
	else if (day % 10 == 3 && day != 13)
		en = "rd";	
	oss << RED " [Error]" ITALIC " Nice try, but the " << _day << en << " of " << calendar[_month] << " " << _year << " is pure fiction." << RESET;
	_msg = oss.str();
}

const char* BtcMap::WrongSpecialDate::what() const throw()
{
	return _msg.c_str();
}

//  SURCHARGE		    ////////////////////////////////////////////////////////
std::ostream &operator<<(std::ostream &out, BtcMap &data)
{
	const std::map<std::string, float>&dataRef = data.getDataMap();
	
	out << YELLOW BOLD "Here is the database :" RESET << std::endl;
	for (std::map<std::string, float>::const_iterator it = dataRef.begin(); it != dataRef.end(); it++)
	{
		out << "[ " GREEN << std::fixed << std::setprecision(0) << it->second << RESET " ] - " BLUE << it->first << RESET << std::endl;
	}
	out << std::endl;

	return out;
}





//	APPRENTISSAGE ++				////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------//

//	std::fixed << std::setprecision(0), permettent de ne pas affiche un float en ecriture scientifique,
// et de ne pas afficher les chiffres apres la virgule.


///////////// C++11 ///////   ;'(   //////////////////////////////////////////////
	// std::tm	time = {};
//	Convertion de la String en StringStream (plus simple et secure pour gerer les erreurs)
	// std::istringstream	ss(date);
//	Convertion de cette StringStream en format date (std::tm) manipulable en c++
//	Grace au second argument de get_time(), on specifie le format, qui renvoie une erreur
// si le format est mauvais dans la StringStream
	// ss >> std::get_time(&time, "%Y-%m-%d");
	// if (ss.fail())
	// {
	// 	throw std::runtime _error("Invalid date format.");
	// }


//	La boucle continue tant que la date est superieure au premier bloc de Bitcoins de la database
// (comparaison lexicographique de chaines)
	// for (; date >= "2009-01-02";)