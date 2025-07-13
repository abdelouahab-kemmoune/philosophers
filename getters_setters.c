/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:37:49 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/13 17:37:51 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//BOOL
void set_bool(t_mtx *mtx, bool *dest, bool value)
{
    safe_mutex_handle(mtx, LOCK);
    *dest = value;
    safe_mutex_handle(mtx, UNLOCK);
}

bool get_bool(t_mtx *mtx, bool *value)
{
    bool ret;

    safe_mutex_handle(mtx, LOCK);
    ret = *value;
    safe_mutex_handle(mtx, UNLOCK);
    return (ret);
}


//LONG
void set_long(t_mtx *mtx, bool *dest, bool value)
{
    safe_mutex_handle(mtx, LOCK);
    *dest = value;
    safe_mutex_handle(mtx, UNLOCK);
}

bool get_long(t_mtx *mtx, bool *value)
{
    bool ret;

    safe_mutex_handle(mtx, LOCK);
    ret = *value;
    safe_mutex_handle(mtx, UNLOCK);
    return (ret);
}

bool simulation_finished(t_table *table)
{
    return (get_bool(&table->table_mutex, &table->end_simulation));
}
