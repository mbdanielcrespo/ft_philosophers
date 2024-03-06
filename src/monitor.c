/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:33:29 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/05 10:57:52 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// Simulation ends before 1000 because someone dies but cannot be writen
int has_died(t_philo *philo)
{
	if (elapsed_time_ms(philo->last_meal) >= philo->table->time_to_die)
	{
		mutex_handle(&philo->table->mtx, LOCK);
		if (has_someone_died(philo))
			return (1);
		philo->is_dead = 1;
		printf("%lld %d DIED\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
		mutex_handle(&philo->table->mtx, UNLOCK);
		return (1);
	}
	return (0);
}

int	has_someone_died(t_philo *philo)
{
	int	res;

	mutex_handle(&philo->table->mtx, LOCK);
	res = philo->table->end;
	mutex_handle(&philo->table->mtx, UNLOCK);
	return (res);
}

void*   monitor_routine(void *arg)
{
	t_table *table;
	int     c;

	table = *(t_table**) arg;
	while (!table->end)
	{
		c = 0;
		mutex_handle(&table->mtx, LOCK);
		while (c < table->num_of_philos)
		{
			if (table->philos[c].is_dead)
			{
				table->end = 1;
				break;
			}
			c++;
		}
		mutex_handle(&table->mtx, UNLOCK);
		if (table->end)
			break;
		usleep(10);
	}
	return (NULL);
}
