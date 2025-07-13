/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:49:46 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/13 18:49:48 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    if (TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
        printf(M"%-6ld"RST" %d has taken a fork🍽️​\n", elapsed, philo->id);
    else if (EATING == status && !simulation_finished(philo->table))
        printf(G"%-6ld"RST" %d is eating🍔​\n", elapsed, philo->id);
    else if (SLEEPING == status && !simulation_finished(philo->table))
        printf(Y"%-6ld"RST" %d is sleeping​😴​\n", elapsed, philo->id);
    else if (THINKING == status && !simulation_finished(philo->table))
        printf(C"%-6ld"RST" %d is thinking🤔​\n", elapsed, philo->id);
    else if (DIED == status)
        printf(RED"%-6ld"RST" %d died💀​\n", elapsed, philo->id);
}


void write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long elapsed;

    elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
    if (philo->full)
        return;
    safe_mutex_handle(&philo->table->write_lock, LOCK);
    if (debug)
        write_status_debug(status, philo, elapsed);
    else
    {
        if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
            && !simulation_finished(philo->table))
            printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
        else if (EATING == status && !simulation_finished(philo->table))
            printf(W"%-6ld"RST" %d is eating\n", elapsed, philo->id);
        else if (SLEEPING == status && !simulation_finished(philo->table))
            printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
        else if (THINKING == status && !simulation_finished(philo->table))
            printf(W"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
        else if (DIED == status)
            printf(W"%-6ld"RST" %d died\n", elapsed, philo->id);
    }
    safe_mutex_handle(&philo->table->write_lock, UNLOCK);
}