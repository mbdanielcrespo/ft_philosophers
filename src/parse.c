/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:32:17 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/15 15:42:17 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

char	*valid_input(char *str)
{
	int c;
	char *num;

	c = 0;
	num = NULL;
	while (str[c])
	{
		while (is_space(str[c]) && str[c])
			c++;
		if (str[c] == '+' && str[c])
			c++;
		else if (str[c] == '-' && str[c])
			error_exit("Only positive values are alowed!\n");
		if (!is_digit(str[c]) && str[c])
			error_exit("Invalid digit input!\n");
		num = &str[c];
		c++;
		break;
	}
	return (num);
}

int	ft_atol(char *str)
{
	int		c;
	char	*num;
	long	ret;

	c = 0;
	ret = 0;
	num = valid_input(str);
	while (is_digit(str[c]))
	{
		ret = ret * 10 + (str[c] - '0');
		c++;
	}
	if (ret >= INT_MAX)
		error_exit("Number too large!\n");	
	return (ret);
}

void	parse_input(t_table *table, char **av)
{
	table->num_of_philos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Use timestamps > 60ms");
	if (av[4])
		table->max_meals = ft_atol(av[5]);
	else
		table->max_meals = -1;
}