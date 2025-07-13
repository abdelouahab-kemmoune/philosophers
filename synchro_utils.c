/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:57:52 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/13 17:57:54 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void wait_all_threads(t_table *table)
{
    while (!get_bool(&table->table_mutex, &table->all_threads_ready))
        ;
}