/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:51:39 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/11 18:51:42 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define RST "\033[0m"
# define RED "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;37m"

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKEN_A_FORK,
	DIED,
}	t_philo_status;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_t			thread_id;
	pthread_mutex_t		philo_mutex;
	t_table				*table;
}	t_philo;

struct s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				start_simulation;
	long				threads_running_nbr;
	long				philos_full;
	bool				end_simulation;
	bool				all_threads_ready;
	pthread_mutex_t		*forks;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		write_mutex;
	t_philo				*philos;
	pthread_t			monitor;
};

void	error_exit(char *error);
long	gettime(void);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);
void	parse_input(t_table *table, char **av);
void	dinner_start(t_table *table);
void	*monitor_dinner(void *data);
void	write_status(t_philo_status status, t_philo *philo);
void	data_init(t_table *table);
void	wait_all_threads(t_table *table);
bool	all_threads_running(pthread_mutex_t *mutex,
			long *threads, long philo_nbr);
void	increase_long(pthread_mutex_t *mutex, long *value);
void	de_synchronize_philos(t_philo *philo);
void	set_bool(pthread_mutex_t *mtx, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mtx, bool *value);
void	set_long(pthread_mutex_t *mtx, long *dest, long value);
long	get_long(pthread_mutex_t *mtx, long *value);
bool	sim_finished(t_table *table);
long	ft_atol(char *str);

#endif
