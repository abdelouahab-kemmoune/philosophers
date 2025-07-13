/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:24:26 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/12 16:24:32 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void assign_forks(t_philo *philo, t_fork *forks,
        int philo_position)
{
    int philo_nbr;
    philo_nbr = philo->table->philo_nbr;

    philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
    philo->second_fork = &forks[philo_position];
    if (philo_position % 2 == 0)
    {
        philo->first_fork = &forks[philo_position];
        philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
    }
}

static void philo_init(t_table *table)
{
    int i;
    t_philo *philo;

    i = -1;
    while (++i < table->philo_nbr)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meals_counter = 0;
        philo->table = table;


        assign_forks(philo, table->forks, i);
    }
}

void data_init(t_table *table)
{
    int i;

    i = -1;
    table->end_simulation = false;
    table->all_threads_ready = false;
    table->philos = safe_malloc(table->philo_nbr * sizeof(t_philo));
    safe_mutex_handle(&table->table_mutex, INIT);
    table->forks = safe_malloc(table->philo_nbr * sizeof(t_fork));
    while (++i < table->philo_nbr)
    {
        safe_mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
    }
    philo_init(table);
}
