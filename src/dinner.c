/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:17:31 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/09 17:39:46 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <math.h>

int	philo_eat(t_philo *philo)
{
	take_forks(philo);
	if (has_philo_died(philo))
	{
		drop_forks(philo);
		return (0);
	}
	increase_meal_counter(philo);
	write_text("is eating", philo);
	if (custom_wait(philo->table->time_to_eat, philo, 1))
		return (0);
	if (philo->n_meals == philo->table->max_meals)
	{
		drop_forks(philo);
		return (0);
	}
	philo->last_meal = current_time_ms();
	drop_forks(philo);
	return (1);
}

void	philo_think(t_philo *philo)
{
	if (has_philo_died(philo))
		return ;
	write_text("is thinking", philo);
}

void	philo_sleep(t_philo *philo)
{
	if (has_philo_died(philo))
		return ;
	write_text("is sleeping", philo);
	custom_wait(philo->table->time_to_sleep, philo, 2);
}


void	*philosopher_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	philo->last_meal = current_time_ms();
	if ((philo->id % 2) == 0 && philo->id != 1)
		usleep(1500);
	while (1)
	{
		philo_think(philo);
		if (!philo_eat(philo))
			break;
		philo_sleep(philo);
		//usleep(abs(philo->table->time_to_eat - philo->table->time_to_sleep) * 1000);
		if (has_philo_died(philo))
			break;
	}
	return (NULL);
}