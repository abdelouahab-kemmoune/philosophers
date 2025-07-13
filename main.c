/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:51:06 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/11 18:51:09 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_table table;
    if (5 == ac || 6 == ac)
    {
        parse_input(&table, av);
        data_init(&table);
        dinner_start(&table);
        clean(&table);
    }
    else
    {
        error_exit("Wrong input:\n"
                   G"Correct is ./philo 5 800 200 200 [5]"RST);
        
    }
}
