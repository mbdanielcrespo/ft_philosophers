/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:04:17 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/07 15:01:12 by danalmei         ###   ########.fr       */
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

int	custom_wait(int wait_ms, t_philo *philo)
{
	long long start_time;

	start_time = current_time_ms();
	while (elapsed_time_ms(start_time) < wait_ms)
	{
		if (have_i_died(philo))
			return (1);
		usleep(50);
	}
	return (0);
}