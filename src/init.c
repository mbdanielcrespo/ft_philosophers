/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:57:13 by danalmei          #+#    #+#             */
/*   Updated: 2023/12/27 15:06:30 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    data_init(t_table *table)
{
    table->end = 0;
    table->philos = safe_malloc(table->philo_nbr); 
}