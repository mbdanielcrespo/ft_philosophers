/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:33:31 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/11 12:18:36 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac >= 4)
	{
		table = (t_table *)malloc(sizeof(t_table));
		if (error_checking(table, av))
			return (1);
		init_threads(table);
	}
	else
	{
		printf("Invalid number of arguments!\n");
		return (1);
	}
	end_simulation(table);
	return (0);
}

int	error_checking(t_table *table, char **av)
{
	if (!table)
	{
		printf("Malloc error!\n");
		return (1);
	}
	if (!parse_input(table, av))
	{
		printf("Parse error!\n");
		return (1);
	}
	if (!init_table(table))
	{
		end_simulation(table);
		return (1);
	}
	return (0);
}
