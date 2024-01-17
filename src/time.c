/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:04:17 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/17 15:43:16 by danalmei         ###   ########.fr       */
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

void	custom_sleep_ms(int ms)
{
	long long start_time;
	long long end_time;

	start_time = current_time_ms();
	end_time = start_time + ms;
	while (current_time_ms() < end_time)
		usleep(1000);
}

// Confirmar se alguem morreu durante o custom sleep