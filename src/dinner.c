/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:17:31 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/05 10:56:16 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	even_philo_eat(t_philo *philo)
{
	mutex_handle(&philo->right_fork->mtx, LOCK);
	printf("%lld %d has taken a fork\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	mutex_handle(&philo->left_fork->mtx, LOCK);
	printf("%lld %d has taken a fork\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	printf("%lld %d is eating\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	if (custom_wait(philo->table->time_to_eat, philo))
	{
		
		mutex_handle(&philo->right_fork->mtx, UNLOCK);
		mutex_handle(&philo->left_fork->mtx, UNLOCK);
		return (0);
	}
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
	if (custom_wait(philo->table->time_to_eat, philo))
	{
		mutex_handle(&philo->left_fork->mtx, UNLOCK);
		mutex_handle(&philo->right_fork->mtx, UNLOCK);
		return (0);
	}
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
	if (has_died(philo) || has_someone_died(philo))
		return (0);
	printf("%lld %d is thinking\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	printf("%lld %d is sleeping\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	if (custom_wait(philo->table->time_to_sleep, philo))
		return (0);
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	if ((philo->id % 2) == 0)
		custom_wait(1, philo);
	while (1)
	{
		mutex_handle(&philo->table->mtx, LOCK);
		if (philo->table->end)
		{
			mutex_handle(&philo->table->mtx, UNLOCK);
			break;
		}
		mutex_handle(&philo->table->mtx, UNLOCK);
		if (!philo_think(philo))
			break;
		if (!philo_eat(philo))
			break;
		if (!philo_sleep(philo))
			break;
	}
	return (NULL);
}