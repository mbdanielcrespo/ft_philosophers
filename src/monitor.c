/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:33:29 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/07 14:59:50 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_end(t_philo *philo)
{
	mutex_handle(&philo->table->mtx, LOCK);
	if (philo->table->end)
	{
		mutex_handle(&philo->table->mtx, UNLOCK);
		return (1);
	}
	mutex_handle(&philo->table->mtx, UNLOCK);
	return (0);
}

int	has_ended(t_philo *philo)
{
	if (has_someone_died(philo) || is_someone_full(philo))
		return (1);
	return (0);
}

int	have_i_died(t_philo *philo)
{
	mutex_handle(&philo->table->mtx, LOCK);
	if (elapsed_time_ms(philo->last_meal) >= philo->table->time_to_die)
	{
		printf("%lld %d DIED\n", elapsed_time_ms(philo->table->dinner_start), philo->id);
		philo->is_dead = 1;
		philo->table->end = 1;
		mutex_handle(&philo->table->mtx, UNLOCK);
		return (1);
	}
	mutex_handle(&philo->table->mtx, UNLOCK);
	return (0);
}

int	is_someone_full(t_philo *philo)
{
	if (philo->table->max_meals == -1)
		return (0);
	if (check_end(philo))
		return (1);
	mutex_handle(&philo->table->mtx, LOCK);
	if (philo->n_meals >= philo->table->max_meals)
	{
		printf("Philo meals: %d\n Max meals: %d\n", philo->n_meals, philo->table->max_meals);
		philo->table->end = 1;
		mutex_handle(&philo->table->mtx, UNLOCK);
		return (1);
	}
	mutex_handle(&philo->table->mtx, UNLOCK);
	return (0);
}

