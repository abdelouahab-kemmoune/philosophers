/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:16:52 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/13 17:16:55 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;

    wait_all_threads(philo->table);

    while (!simulation_finished(philo->table))
    {
        if (philo->full)
            break ;
        eat(philo);
        
        write_status(SLEEPING, philo, DEBUG_MODE);
        precise_usleep(philo->table->time_to_sleep, philo->table);
        //think(philo);
    }

    return (NULL);
}





void dinner_start(t_table *table)
{
    int i;

    i = -1;
    if (table->nbr_limit_meals == 0)
        return ;
    else if (table->philo_nbr == 1)
        ;
    else
    {
        while (i++ < table->philo_nbr)
            safe_thread_handle(&table->philos[i].thread_id,
                    dinner_simulation, &table->philos[i], CREATE);
    }
    table->start_simulation = gettime(MILLISECOND);
    set_bool(&table->table_mutex, &table->all_threads_ready, true);
    i = -1;
    while (i++ < table->philo_nbr)
        safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
}