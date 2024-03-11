/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:33:29 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/11 12:01:13 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	take_fork(t_philo *philo, t_fork *taken_fork)
{
	mutex_handle(&taken_fork->mtx, LOCK);
	if (!has_philo_died(philo))
		write_text("has taken a fork", philo);
}

void	take_forks(t_philo *philo)
{
	if ((philo->id % 2) == 1)
	{
		take_fork(philo, philo->right_fork);
		take_fork(philo, philo->left_fork);
	}
	else
	{
		take_fork(philo, philo->left_fork);
		take_fork(philo, philo->right_fork);
	}
}

void	drop_forks(t_philo *philo)
{
	if ((philo->id % 2) == 1)
	{
		mutex_handle(&philo->left_fork->mtx, UNLOCK);
		mutex_handle(&philo->right_fork->mtx, UNLOCK);
	}
	else
	{
		mutex_handle(&philo->right_fork->mtx, UNLOCK);
		mutex_handle(&philo->left_fork->mtx, UNLOCK);
	}
}
