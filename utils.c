/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:55:10 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/11 18:55:11 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long gettime(t_time_code time_code)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        error_exit("Gettimeofday failed");
    if (time_code == SECOND)
        return (tv.tv_sec + (tv.tv_usec / 1e6));
    else if (time_code == MILLISECOND)
        return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (time_code == MICROSECOND)
        return ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_exit("Wrong input to gettime!");
    return (1337);
}


void precise_usleep(long usec, t_table *table)
{
    long start;
    long elapsed;
    long rem;

    start = gettime(MICROSECOND);
    while (gettime(MICROSECOND) - start < usec)
    {
        if (simulation_finished(table))
            break ;
        elapsed = gettime(MICROSECOND) - start;
        rem = usec - elapsed;
        if (rem > 1e3)
            usleep(rem / 2);
        else
        {
            while (gettime(MICROSECOND) - start < usec)
                ;
        }
    }
}


void    error_exit(const char *error)
{
    printf(RED"" "Error: %s\n", error);
    exit(EXIT_FAILURE);
}
