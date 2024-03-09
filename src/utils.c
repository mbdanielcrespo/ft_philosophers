/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:41:58 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/08 00:02:40 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int is_digit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int is_space(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32)
		return (1);
	return (0);
}

void	increase_meal_counter(t_philo *philo)
{
	if (philo->table->max_meals != -1)
		philo->n_meals += 1;
}


void	write_text(char *text, t_philo *philo)
{
	mutex_handle(&philo->table->log, LOCK);
	printf("%lld %d %s\n", elapsed_time_ms(philo->table->dinner_start), philo->id, text);
	mutex_handle(&philo->table->log, UNLOCK);
}

void	mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		pthread_mutex_lock(mutex);
	else if (UNLOCK == opcode)
		pthread_mutex_unlock(mutex);
	else if (INIT == opcode)
		pthread_mutex_init(mutex, NULL);
	else if (DESTROY == opcode)
		pthread_mutex_destroy(mutex);
	else
		printf("Wrong code!\n");
}
