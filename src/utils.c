/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:41:58 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/15 15:34:05 by danalmei         ###   ########.fr       */
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

void	error_exit(char *error)
{
	printf("%s\n", error);
	exit(1);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit("Malloc error");
	return (ret);
}

void	handle_mutex_error(int stat, t_opcode opcode)
{
	if (stat == 0)
		return ;
	if (EINVAL == stat && (LOCK == opcode || UNLOCK == opcode))
		error_exit("Value specified by mutex is invalid!");
	if (EINVAL == stat && INIT == opcode)
		error_exit("Value specified by atte is invalid");
	else if (EDEADLK == stat)
		error_exit("A deadlock would occur, thread blocked waiting for mutex");
	else if (EPERM == stat)
		error_exit("Current thread does not have a lock/mutex");
	else if (ENOMEM == stat)
		error_exit("The process cannot allocate enough memory");
	else if (EBUSY == stat)
		error_exit("Thread is busy !!!!!************");
}

void    safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle");
}