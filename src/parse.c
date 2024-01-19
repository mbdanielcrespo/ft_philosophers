/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:32:17 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/19 14:41:57 by danalmei         ###   ########.fr       */
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
			return (num);
		if (!is_digit(str[c]) && str[c])
			return (num);
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
	if (!num)
		return (0);
	while (is_digit(str[c]))
	{
		ret = ret * 10 + (str[c] - '0');
		c++;
	}
	if (ret >= INT_MAX)
	{
		printf("Number too large!\n");
		return (0);
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