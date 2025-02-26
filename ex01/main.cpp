/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:40:01 by fcoullou          #+#    #+#             */
/*   Updated: 2025/02/26 13:58:51 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << RED "[ERROR]" ITALIC " You need a Reverse Polish Notation to run this program !" RESET << std::endl;
        return 1;
    }

    RPN myStack;
	try
	{
		myStack.parseAndExec(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
        
    return 0;
}