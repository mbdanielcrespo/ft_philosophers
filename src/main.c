/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:33:31 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/16 14:58:31 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
// 5 200 200 200 [5]
int main(int ac, char **av)
{
	t_table *table;
	long long	curr_time;
	
	printf("Program started ...\n");
	curr_time = current_time_ms();
	if (ac >= 4)
	{
		table = (t_table *)safe_malloc(sizeof(t_table));
		init_table(table, av);		// Parse input and allocate variables
		print_all(table);			// Debug print
		init_philos_threads(table);
		// Simulation
		// Cleanup
	}
	else
		error_exit("Invalid number of arguments!\n");
	printf("Program finished ... elapsed time: %lldms\n", elapsed_time_ms(curr_time));
	return (0);
}