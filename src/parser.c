/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:04:24 by danalmei          #+#    #+#             */
/*   Updated: 2023/12/27 13:30:34 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		is_digit(char c)
{
	return (c >= 48 && c <= 57);
}

int	is_space(char c)
{	
	return ((c >= 9 && c <= 13) || 32 == c); 
}

char    *valid_input(char *str)
{
	int     c;
	int		len;
	char    *num;

	c = 0;
	while (is_space(str[c]))
		c++;
	if (str[c] == '+')
		c++;
	else if (str[c] == '-')
		error_exit("Only positive values alowed!");
	if (!is_digit(str[c]))
		error_exit("Invalid digit input"); 
	num = str;
	while (is_digit(str[c]))
	{
		c++;
		len++;
	}
	if (len > 10)
		error_exit("Value is too big, INT_MAX is the maximum");
	return(num);
}

long    ft_atol(char *str)
{
	int		c;
	long    num;

	c = 0;
	num = 0;
	str = valid_input(str);
	while (is_digit(str[c]))
	{
		num = (num * 10) + (str[c] - 48);
		c++;
	}
	if (num > INT_MAX)
		error_exit("Value is too big, INT_MAX is the maximum");
	return (num);
}

void    parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Use timestamps > 60ms");
	else
		table->meals_limit = ft_atol(av[5]);
}