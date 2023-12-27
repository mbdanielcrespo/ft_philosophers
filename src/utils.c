/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:51:07 by danalmei          #+#    #+#             */
/*   Updated: 2023/12/27 15:30:05 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_exit(char *error)
{
	printf("ERROR: %s\n", error);
	exit(EXIT_FAILURE);
}

void    safe_malloc(size_t bytes)
{
	void    *ret;
	
	ret = malloc(bytes);
	if (NULL == ret)
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
		error_exit("The process cannot allocate enough memory")
	else if (EBUSY == stat)
		error_exit()
}

void    safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
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
		error_exit("Wrong opcode for mutex handle");
}