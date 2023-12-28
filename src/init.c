/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:57:13 by danalmei          #+#    #+#             */
/*   Updated: 2023/12/28 11:19:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
    int philo_nbr;

    philo_nbr = philo->table->philo_nbr;
    philo->first_fork = &forks[philo_pos];
    philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
    if (philo->philo_id % 2)
    {
        philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
        philo->second_fork = &forks[philo_pos];
    }
}

void    philo_init(t_table *table)
{
    int c;
    t_philo *philo;

    c = 0;
    while (c < table->philo_nbr)
    {
        philo = table->philos + c;
        philo->philo_id = c + 1;
        philo->is_full = 0;
        philo->nbr_meals = 0;
        philo->table = table;
        philo->all_threads_sync = 0;
        assign_forks(philo, table->forks, c);
    }
}

void    data_init(t_table *table)
{
    int c;

    c = 0;
    table->end = 0;
    table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr); 
    table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr); 
    safe_mutex_handle(table->table_mutex, INIT);
    while (c < table->philo_nbr)
    {
        safe_mutex_handle(&table->forks[c].fork, INIT);
        table->forks[c].fork_id = c;
        c++;
    }
    philo_init(table);
}