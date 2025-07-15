/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:18:22 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/15 15:18:23 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_died(t_philo *philo)
{
    long elapsed;
    long t_to_die;

    if (get_bool(&philo->philo_mutex, &philo->full))
        return (false);
    elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
    t_to_die = philo->table->time_to_die / 1e3;
    if (elapsed > t_to_die)
        return (true);
    return (false);
}

void *monitor_dinner(void *data)
{
    t_table *table;
    int i;

    table = (t_table *)data;
    while (!all_threads_running(&table->table_mutex, &table->threads_rununing_nbr,
                table->philo_nbr))
        ;
    while (!simulation_finished(table))
    {
        i = -1;
        while (++i < table->philo_nbr && !simulation_finished(table))
        {
            if (philo_died(table->philos + i))
            {
                set_bool(&table->table_mutex, &table->end_simulation, true);
                write_status(DIED, table->philos + i, DEBUG_MODE);
            }
        }
        // Check if all philosophers are full (finished eating required meals)
        if (table->nbr_limit_meals > 0)
        {
            i = -1;
            while (++i < table->philo_nbr)
            {
                if (!get_bool(&table->philos[i].philo_mutex, &table->philos[i].full))
                    break;
            }
            if (i == table->philo_nbr) // All philosophers are full
                set_bool(&table->table_mutex, &table->end_simulation, true);
        }
    }
    return (NULL);
}
