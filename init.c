/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:24:26 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/16 14:01:20 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[i];
		if (philo->id == philo_nbr)
			philo->second_fork = &forks[0];
		else
			philo->second_fork = &forks[philo->id];
	}
	else
	{
		philo->second_fork = &forks[i];
		if (philo->id == philo_nbr)
			philo->first_fork = &forks[0];
		else
			philo->first_fork = &forks[philo->id];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->last_meal_time = 0;
		philo->table = table;
		pthread_mutex_init(&philo->philo_mutex, NULL);
		assign_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->philos_full = 0;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	pthread_mutex_init(&table->table_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	while (++i < table->philo_nbr)
		pthread_mutex_init(&table->forks[i], NULL);
	philo_init(table);
}
