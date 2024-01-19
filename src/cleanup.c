/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:11:57 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/19 15:00:27 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void    join_philos_threads(t_table *table)
{
	int c;

	c = 0;
	while (c < table->num_of_philos)
	{
		pthread_join(table->philos[c].philo, NULL);
		c++;
	}
}

void    destroy_mutexes(t_table *table)
{
	int c;

	c = 0;
	while (c < table->num_of_philos)
	{
		mutex_handle(&table->forks[c].mtx, DESTROY);
		c++;
	}
}

void    destroy_structures(t_table *table)
{
	free(table->philos);
	free(table->forks);
}

void    end_simulation(t_table *table)
{
	join_philos_threads(table);
	destroy_mutexes(table);
	destroy_structures(table);
}
