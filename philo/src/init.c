/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:16:49 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/11 12:15:57 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	init_table(t_table *table)
{
	table->end = 0;
	table->dinner_start = current_time_ms();
	mutex_handle(&table->mtx, INIT);
	mutex_handle(&table->log, INIT);
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->n_philos);
	if (!table->philos)
		return (0);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->n_philos);
	if (!table->forks)
		return (0);
	init_forks(table);
	init_philos(table);
	return (1);
}

void	init_forks(t_table *table)
{
	int	c;

	c = 0;
	while (c < table->n_philos)
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
	while (c < table->n_philos)
	{
		table->philos[c].id = c + 1;
		table->philos[c].last_meal = table->dinner_start;
		table->philos[c].n_meals = 0;
		table->philos[c].is_dead = 0;
		table->philos[c].left_fork = &table->forks[c];
		table->philos[c].right_fork = &table->forks[(c + 1) % table->n_philos];
		table->philos[c].table = table;
		c++;
	}
}

void	init_threads(t_table *table)
{
	int	c;

	c = 0;
	while (c < table->n_philos)
	{
		if (table->n_philos == 1)
		{
			if (pthread_create(&table->philos[c].philo, NULL, 
					one_philo, (void *)&table->philos[c]) != 0)
			{
				printf("Error creating philo thread!\n");
				return ;
			}
		}
		else
		{
			if (pthread_create(&table->philos[c].philo, NULL, 
					philosopher_routine, (void *)&table->philos[c]) != 0)
			{
				printf("Error creating philo thread!\n");
				return ;
			}
		}
		c++;
	}
}
