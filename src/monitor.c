/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:33:29 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/24 00:20:27 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// Instead of only checking itself it has to check simulation end ***
int has_died(t_philo *philo)
{
	if (elapsed_time_ms(philo->last_meal) >= philo->table->time_to_die)
	{
		philo->is_dead = 1;
		printf("%lld %d died\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
		return (1);
	}
	return (0);
}

void*   monitor_routine(void *arg)
{
	t_table *table;
	int     c;
	int		found;

	table = (t_table*) arg;
	while (!table->end)
	{
		c = 0;
		found = 0;
		pthread_mutex_lock(&table->mtx);
		while (c < table->num_of_philos)
		{
			if (table->philos[c].is_dead)
			{
				table->end = 1;
				found = 1;
				break;
			}
			c++;
		}
		pthread_mutex_unlock(&table->mtx);
		if (found)
			break;
		usleep(100);
	}
	return (NULL);
}
