/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:04:17 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/08 19:14:49 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	current_time_ms(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

long long	elapsed_time_ms(long long start_time)
{
	long long end_time;
	
	end_time = current_time_ms();
	return (end_time - start_time);
}

void	custom_wait(int wait_ms, t_philo *philo, int flag)
{
	long long start_time;

	start_time = current_time_ms();
	while (elapsed_time_ms(start_time) < wait_ms)
	{
		if (has_philo_died(philo))
		{
			if (flag == 1)
			{
				drop_forks(philo);	
				return ;
			}
			else if (flag == 2)
				return ;
		}
		usleep(1);
	}
}

int	has_philo_died(t_philo *philo)
{	
	mutex_handle(&philo->table->mtx, LOCK);
	if (philo->table->end)
	{
		mutex_handle(&philo->table->mtx, UNLOCK);
		return (1);
	}
	if (elapsed_time_ms(philo->last_meal) >= philo->table->time_to_die)
	{
		philo->table->end = 1;
		printf("%lld %d %s\n", elapsed_time_ms(philo->table->dinner_start), philo->id, "is DEAD");
		mutex_handle(&philo->table->mtx, UNLOCK);
		return (1);
	}
	mutex_handle(&philo->table->mtx, UNLOCK);
	return (0);
}