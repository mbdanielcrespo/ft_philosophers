/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:17:31 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/08 19:37:28 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	even_philo_eat(t_philo *philo)
{
	mutex_handle(&philo->right_fork->mtx, LOCK);
	if (write_text("has taken a fork", philo))
	{
		mutex_handle(&philo->right_fork->mtx, UNLOCK);
		return (0);
	}
	mutex_handle(&philo->left_fork->mtx, LOCK);
	if (write_text("has taken a fork", philo))
	{
		mutex_handle(&philo->right_fork->mtx, UNLOCK);
		mutex_handle(&philo->left_fork->mtx, UNLOCK);
		return (0);
	}
	if (write_text("is eating", philo))
	{
		mutex_handle(&philo->right_fork->mtx, UNLOCK);
		mutex_handle(&philo->left_fork->mtx, UNLOCK);
		return (0);
	}
	//increase_meal_counter(philo);
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
	if (write_text("has taken a fork", philo))
	{
		mutex_handle(&philo->left_fork->mtx, UNLOCK);
		return (0);
	}
	mutex_handle(&philo->right_fork->mtx, LOCK);
	if (write_text("has taken a fork", philo))
	{
		mutex_handle(&philo->left_fork->mtx, UNLOCK);
		mutex_handle(&philo->right_fork->mtx, UNLOCK);
		return (0);
	}
	if (write_text("is eating", philo))
	{
		mutex_handle(&philo->left_fork->mtx, UNLOCK);
		mutex_handle(&philo->right_fork->mtx, UNLOCK);
		return (0);
	}
	//increase_meal_counter(philo);
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

void	take_fork(t_fork *take_fork)
{
	
}

void	philo_eat(t_philo *philo)
{
	if ((philo->id % 2) == 1)
	{
		take_fork(philo->right_fork);
		take_fork(philo->left_fork);
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
	//printf("%lld %d is thinking\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	if (write_text("is thinking", philo))
		return (0);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	//printf("%lld %d is sleeping\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	if (write_text("is sleeping", philo))
		return (0);
	if (custom_wait(philo->table->time_to_sleep, philo))
		return (0);
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	philo->last_meal = current_time_ms();
	if ((philo->id % 2) == 0 && philo->id != 1)
		usleep(50);
	while (1)
	{
		//if (is_philo_dead(philo))
		//	break;
		philo_eat(philo);		
		if (!philo_think(philo))
			break;
		if (!philo_sleep(philo))
			break;
	}
	return (NULL);
}