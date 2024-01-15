/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:17:31 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/15 15:52:51 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    philo->is_dead = 0;

    return (NULL);
}