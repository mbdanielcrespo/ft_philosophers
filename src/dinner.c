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

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	if (has_philo_died(philo))
	{
		drop_forks(philo);
		return ;
	}
	printf("%lld %d %s\n", elapsed_time_ms(philo->table->dinner_start), philo->id, "is eating");
	custom_wait(philo->table->time_to_eat, philo, 1);
	increase_meal_counter(philo);
	if (philo->n_meals == philo->table->max_meals)
	{
		mutex_handle(&philo->table->mtx, LOCK);
		philo->table->end = 1;
		mutex_handle(&philo->table->mtx, UNLOCK);
	}
	philo->last_meal = current_time_ms();
	drop_forks(philo);
}

void	philo_think(t_philo *philo)
{
	if (has_philo_died(philo))
		return ;
	printf("%lld %d is thinking\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
}

void	philo_sleep(t_philo *philo)
{
	if (has_philo_died(philo))
		return ;
	printf("%lld %d is sleeping\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
	custom_wait(philo->table->time_to_sleep, philo, 2);
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
		if (has_philo_died(philo))
			break;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (has_philo_died(philo))
			break;
	}
	return (NULL);
}