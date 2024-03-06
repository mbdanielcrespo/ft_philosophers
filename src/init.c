/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:16:49 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/06 16:15:47 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int    init_table(t_table *table)
{
	table->end = 0;
	table->dinner_start = current_time_ms();
	mutex_handle(&table->mtx, INIT);
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philos)
		return (0);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->num_of_philos);
	if (!table->forks)
		return (0);
	init_forks(table);
	init_philos(table);
	return (1);
}

// In case mutex fails error
void	init_forks(t_table *table)
{
	int	c;

	c = 0;
	while (c < table->num_of_philos)
	{
		mutex_handle(&table->forks[c].mtx, INIT);
		table->forks[c].id = c;
		c++;
	}
}

void	init_philos(t_table *table)
{
	int	c;

	c = 0;
	while (c < table->num_of_philos)
	{
		table->philos[c].id = c + 1;
		table->philos[c].last_meal = current_time_ms();
		table->philos[c].is_dead = 0;
		table->philos[c].left_fork = &table->forks[c];
		table->philos[c].right_fork = &table->forks[(c + 1) % table->num_of_philos];
		table->philos[c].table = table;
		c++;
	}
}

int	init_threads(t_table *table)
{
	int	c;
	
	c = 0;
	while (c < table->num_of_philos)
	{
		if (pthread_create(&table->philos[c].philo, NULL, philosopher_routine, (void *)&table->philos[c]) != 0)
		{
			printf("Error creating philo thread!\n");
			return (0);
		}
		c++;
	}
	return (1);
}
