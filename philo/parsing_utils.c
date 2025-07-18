/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:15:07 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/12 15:15:10 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_number(char *str)
{
	if (*str == '+')
		str++;
	if (!is_digit(*str))
		return (false);
	while (*str)
	{
		if (!is_digit(*str))
			return (false);
		str++;
	}
	return (true);
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static char	*valid_input(char *str)
{
	while (is_space(*str))
		++str;
	if (*str == '-')
		error_exit("Feed me only positive values sir!");
	if (!is_number(str))
		error_exit("The input is not a correct digit");
	return (str);
}

long	ft_atol(char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > LONG_MAX)
		error_exit("The input is too long, INT_MAX is the limit!");
	return (num);
}
