/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:16:52 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/16 13:58:53 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	write_status(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think, philo->table);
}

void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime());
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	write_status(TAKEN_A_FORK, philo);
	while (!sim_finished(philo->table))
		precise_usleep(philo->table->time_to_sleep, philo->table);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	write_status(TAKEN_A_FORK, philo);
	pthread_mutex_lock(philo->second_fork);
	write_status(TAKEN_A_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime());
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime());
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	while (!sim_finished(philo->table))
	{
		eat(philo);
		if (philo->full)
		{
			increase_long(&philo->table->table_mutex,
				&philo->table->philos_full);
			break ;
		}
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		pthread_create(&table->philos[0].thread_id,
			NULL, lone_philo, &table->philos[0]);
	else
	{
		while (++i < table->philo_nbr)
			pthread_create(&table->philos[i].thread_id, NULL,
				dinner_simulation, &table->philos[i]);
	}
	pthread_create(&table->monitor, NULL, monitor_dinner, table);
	table->start_simulation = gettime();
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	pthread_join(table->monitor, NULL);
}
