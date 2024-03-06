/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:33:31 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/06 16:31:51 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
// 5 200 200 200 [5]
int main(int ac, char **av)
{
	t_table *table;

	if (ac >= 4)
	{
		table = (t_table *)malloc(sizeof(t_table));
		if (!table)
		{
			printf("Malloc error!\n");
			return (1);	
		}
		if (!parse_input(table, av))
			return (1);
		if (!init_table(table))
		{
			end_simulation(table);			//TODO: handle
			return (1);
		}
		if (!init_threads(table))
		{
			end_simulation(table);			//TODO: handle
			return (1);
		}
	}
	else
	{
		printf("Invalid number of arguments!\n");
		return (1);
	}
	end_simulation(table);
	return (0);
}