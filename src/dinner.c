/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:17:31 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/16 15:23:29 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
void	monitor(t_table *table)
{
	pthread_t monitor_thread;

	if (pthread_create(monitor_thread, NULL, philosopher_routine, (void *)&table) != 0)
		error_exit("Error creating thread");
	
}*/

void	*philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	long long	start_time;
	// If philosohper is even take left fork, take right fork, eat then sleep, then think, take left fork ...
	// If philosopher is uneven think, take right fork, take left fork, eat, then sleep, then ...

	while (!philo->table->end)
	{
		philo_think();
		safe_mutex_handle(&philo->left_fork->mtx, LOCK);
		safe_mutex_handle(&philo->right_fork->mtx, LOCK);
		philo_eat(philo);
		safe_mutex_handle(&philo->right_fork->mtx, UNLOCK);
		safe_mutex_handle(&philo->left_fork->mtx, UNLOCK);
		philo_sleep(philo);
	}
	return (NULL);
}

