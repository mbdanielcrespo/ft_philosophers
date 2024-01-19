/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:17:31 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/19 15:00:08 by danalmei         ###   ########.fr       */
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

int	even_philo_eat(t_philo *philo)
{
	mutex_handle(&philo->right_fork->mtx, LOCK);
	printf("%lld %d has taken a fork\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	mutex_handle(&philo->left_fork->mtx, LOCK);
	printf("%lld %d has taken a fork\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	printf("%lld %d is eating\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	custom_wait(philo, philo->table->time_to_eat);
	philo->last_meal = current_time_ms();
	mutex_handle(&philo->right_fork->mtx, UNLOCK);
	mutex_handle(&philo->left_fork->mtx, UNLOCK);
	return (1);
}

int	uneven_philo_eat(t_philo *philo)
{
	mutex_handle(&philo->left_fork->mtx, LOCK);
	printf("%lld %d has taken a fork\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	mutex_handle(&philo->right_fork->mtx, LOCK);
	printf("%lld %d has taken a fork\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	printf("%lld %d is eating\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	custom_wait(philo, philo->table->time_to_eat);
	philo->last_meal = current_time_ms();
	mutex_handle(&philo->left_fork->mtx, UNLOCK);
	mutex_handle(&philo->right_fork->mtx, UNLOCK);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	if ((philo->id % 2) == 1)
	{
		if (!even_philo_eat(philo))
			return (0);
	}
	else
	{
		if (!uneven_philo_eat(philo))
			return (0);
	}
	return (1);
}

int	philo_think(t_philo *philo)
{
	printf("%lld %d is thinking\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	custom_wait(philo, 100);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	printf("%lld %d is sleeping\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	custom_wait(philo, philo->table->time_to_sleep);
	return (1);
}

int has_died(t_philo *philo)
{
	if (elapsed_time_ms(philo->last_meal) >= philo->table->time_to_die)
	{
		printf("%lld %d died\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
		return (1);
	}
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	if ((philo->id % 2) == 0)
		usleep(100);
	while (!philo->table->end)
	{
		if (!philo_think(philo))
			break;
		if (!philo_eat(philo))
			break;
		if (!philo_sleep(philo))
			break;
	}
	printf("SIMULATION FINISHED!\n");
	return (NULL);
}