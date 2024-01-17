/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:17:31 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/17 15:53:09 by danalmei         ###   ########.fr       */
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

int has_died(t_philo *philo, char *debug)
{
	long long	last_meal;
	long long	time_to_die;

	last_meal = philo->last_meal;
	time_to_die = philo->table->time_to_die;
	if (elapsed_time_ms(last_meal) >= time_to_die)
	{
		printf("Elapsed time: %lld, Time_to_die: %lld\n", elapsed_time_ms(last_meal), time_to_die);
		printf("%lld %d died %s\n", elapsed_time_ms(philo->table->dinner_start), philo->id, debug);
		return (1);
	}
	return (0);
}


int	philo_think(t_philo *philo)
{
	printf("%lld %d is thinking\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	if (has_died(philo, "thinking"))
			return (0);
	usleep(100);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	long long eat_start_time;

	safe_mutex_handle(&philo->left_fork->mtx, LOCK);
	printf("%lld %d has taken a fork\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	safe_mutex_handle(&philo->right_fork->mtx, LOCK);
	printf("%lld %d has taken a fork\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	eat_start_time = current_time_ms();
	printf("%lld %d is eating\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	while (elapsed_time_ms(eat_start_time) < philo->table->time_to_eat)
	{
		if (has_died(philo, "eating"))
			return (0);
		usleep(100); // Sleep in small increments to check regularly if the philosopher has died
	}
	philo->last_meal = current_time_ms();
	safe_mutex_handle(&philo->right_fork->mtx, UNLOCK);
	safe_mutex_handle(&philo->left_fork->mtx, UNLOCK);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	long long start_time;

	start_time = current_time_ms();
	printf("%lld %d is sleeping\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	while (elapsed_time_ms(start_time) < philo->table->time_to_sleep)
	{
		if (has_died(philo, "sleeping"))
			return (0);
		usleep(100); // Sleep in small increments to check regularly
	}
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
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

