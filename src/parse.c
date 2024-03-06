/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:32:17 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/04 17:07:52 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	is_valid_input(char *str)
{
	int c;

	c = 0;
	while (is_space(str[c]) && str[c])
		c++;
	if ((str[c] == '+' || str[c] == '-') && str[c])
	{
		if (str[c] == '-')
			return (0);
		c++;
	}
	while (str[c])
	{
		if (!is_digit(str[c]))
			return (0);
		c++;
	}
	return (1);
}

int	ft_atol(char *str)
{
	int		c;
	long	ret;

	c = 0;
	ret = 0;
	if (!is_valid_input(str))
		return (0);
	while (is_space(str[c]))
		c++;
	while (is_digit(str[c]))
	{
		ret = ret * 10 + (str[c] - '0');
		if (ret >= INT_MAX || ret <= INT_MIN)
		{
			printf("Number out of range!\n");
			return (0);
		}
		c++;
	}
	return (ret);
}

int	parse_input(t_table *table, char **av)
{
	if (!ft_atol(av[1]) || !ft_atol(av[2]) || !ft_atol(av[3]) || !ft_atol(av[4]))
		return (0);
	table->num_of_philos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (av[5])
	{
		if (!ft_atol(av[1]))
			return (0);
		table->max_meals = ft_atol(av[5]);
	}
	else
		table->max_meals = -1;
	return (1);
}