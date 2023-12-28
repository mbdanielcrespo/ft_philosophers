/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:09:07 by marvin            #+#    #+#             */
/*   Updated: 2023/12/28 11:09:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;

    wait_all_threads(philo->table);

    return (NULL);
}

void    start(t_table *table)
{
    int c;

    c = 0;
    if (table->meals_limit == 0)
        return ;
    else if (table->philo_nbr == 1)
    {
        
    }
    else
    {
        while (c < table->philo_nbr)
        {
            safe_thread_handle(&table->philos[c].thread_id, dinner_simultaion,
                    &table->philos[c], CREATE);
            
        }
    }

    
    
    
}