/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:16:49 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/16 15:22:53 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void    init_table(t_table *table, char **av)
{
	parse_input(table, av);
	table->end = 0;
	table->philos = (t_philo *)safe_malloc(sizeof(t_philo) *
										table->num_of_philos);
	table->forks = (t_fork *)safe_malloc(sizeof(t_fork) *
										table->num_of_philos);
	init_forks(table);
	init_philos(table);
}

void	init_forks(t_table *table)
{
	int	c;

	c = 0;
	while (c < table->num_of_philos)
	{
		safe_mutex_handle(&table->forks[c].mtx, INIT);
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
		table->philos[c].id = c;
		table->philos[c].status = THINKING;
		table->philos[c].is_dead = 0;
		table->philos[c].left_fork = &table->forks[c];
		table->philos[c].right_fork = &table->forks[(c + 1) % table->num_of_philos];
		table->philos[c].table = table;
		c++;
	}
}

void	init_philos_threads(t_table *table)
{
	int	c;

	c = 0;
	while (c < table->num_of_philos)
	{
		if (pthread_create(&table->philos[c].philo, NULL, philosopher_routine, (void *)&table->philos[c]) != 0)
			error_exit("Error creating thread");
		c++;
	}
}

