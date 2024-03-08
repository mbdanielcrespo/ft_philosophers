/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:33:29 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/08 19:31:56 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	write_text(char *text, t_philo *philo)
{
	mutex_handle(&philo->table->mtx, LOCK);
	if (!philo->table->end)
	{
		printf("%lld %d %s\n", elapsed_time_ms(philo->table->dinner_start), philo->id, text);
		mutex_handle(&philo->table->mtx, UNLOCK);
		return (0);
	}
	mutex_handle(&philo->table->mtx, UNLOCK);
	return (1);
}

int	has_philo_died(t_philo *philo)
{	
	//int	current;

	//current = elapsed_time_ms(philo->table->dinner_start);
	if (elapsed_time_ms(philo->last_meal) >= philo->table->time_to_die)
	{
		mutex_handle(&philo->table->mtx, LOCK);
		if (philo->table->end)
		{
			mutex_handle(&philo->table->mtx, UNLOCK);
			return (1);
		}
		else
		{
			philo->table->end = 1;
			printf("%lld %d %s\n", elapsed_time_ms(philo->table->dinner_start), philo->id, "is DEAD");
			mutex_handle(&philo->table->mtx, UNLOCK);
			return (1);
		}
	}
	return (0);
}
/*
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
		//mutex_handle(&philo->table->mtx, UNLOCK);
		return (1);
	}
	mutex_handle(&philo->table->mtx, UNLOCK);
	return (0);
}
*/