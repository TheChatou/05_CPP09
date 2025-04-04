/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:10:07 by fcoullou          #+#    #+#             */
/*   Updated: 2025/04/01 15:03:49 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdexcept>
#include <map>

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

class BtcMap
{
	private :
		std::map<std::string, float>	_data;
		
	public :
	//	CANONICAL FORM		////////////////////////////////////////////////////////
		BtcMap();
		BtcMap(const BtcMap &copy);
		~BtcMap();
		BtcMap &operator=(const BtcMap &copy);
		
	//  GETTERS			    ////////////////////////////////////////////////////////
		std::map<std::string, float>			getDataMap() const;
		std::map<std::string, float>::iterator	getDateCurrency(std::string &date);
		
	//  MEMBER FUNCTIONS    ////////////////////////////////////////////////////////
	//	Parsing the Datas		----------------------------------------------------
		int				parse(std::string &line, bool wichOne);
		std::string		parseDate(std::string &line);
		float			parseValue(std::string &line);
		float			parseAmount(std::string &line);
		void			checkDate(std::string &date) const;
		bool			specialDate(int year, int month, int day) const;

	//	Working the Input		----------------------------------------------------
		int				howMuch(std::string &line);
		float			calcBtc(std::string &date, float amount);

	//  UTILS			    ////////////////////////////////////////////////////////
		bool			isNum(const std::string &str) const;
		bool			isFloat(const std::string &str) const;
		void			welcome() const;
		void			goodbye() const;
		void			printTab() const;

	//  EXCEPTIONS		    ////////////////////////////////////////////////////////
		class WrongDate: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
				
		class WrongInputFormat: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		
		class FutureDate: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		
		class WrongValue: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		
		class WrongAmount: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		
		class WrongSpecialDate: public std::exception
		{
			private :
				int			_year;
				int 		_month;
				int 		_day;
				std::string	_msg;
				
			public:
				WrongSpecialDate(int year, int month, int day);
				virtual ~WrongSpecialDate() throw() {}
				virtual const char* what() const throw();
		};
};

//  SURCHARGE		    ////////////////////////////////////////////////////////
std::ostream &operator<<(std::ostream &out, BtcMap &data);