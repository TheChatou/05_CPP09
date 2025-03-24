/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:26:10 by fcoullou          #+#    #+#             */
/*   Updated: 2025/03/24 15:37:33 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe_class.hpp"

int     wrongInput()
{
    std::cout << RED "Enter valid Input please" RESET << std::endl;
    
    return 1;
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        return wrongInput();
    }

    try
    {
        PmergeMe    input(ac, av);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;            
}