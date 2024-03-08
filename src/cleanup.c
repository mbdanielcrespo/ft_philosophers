/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:11:57 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/08 18:04:22 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	join_threads(t_table *table)
{
	int c;

	c = 0;
	while (c < table->num_of_philos)
	{
		if (pthread_join(table->philos[c].philo, NULL) < 0)
			printf("Thread join error\n");
		c++;
	}
}

void    destroy_mutexes(t_table *table)
{
	int c;

	c = 0;
	mutex_handle(&table->mtx, DESTROY);
	mutex_handle(&table->log, DESTROY);
	while (c < table->num_of_philos)
	{
		mutex_handle(&table->forks[c].mtx, DESTROY);
		c++;
	}
}

void	destroy_structures(t_table *table)
{
	free(table->philos);
	free(table->forks);
}

void	end_simulation(t_table *table)
{
	join_threads(table);
	destroy_mutexes(table);
	destroy_structures(table);
}
