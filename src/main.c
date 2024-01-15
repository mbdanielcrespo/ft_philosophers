/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:33:31 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/15 15:28:37 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
// 5 200 200 200 [5]
int main(int ac, char **av)
{
	t_table *table;

	(void)ac;
	table = (t_table *)safe_malloc(sizeof(t_table));
	init_table(table, av);
	print_all(table);
	
	// Simulation
	// Cleanup
	return (0);
}