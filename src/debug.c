/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:07:40 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/23 23:23:41 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// Table pointer*
void    print_table(t_table *table)
{
    printf("Num of philos: %d\n", table->num_of_philos);
    printf("Time to eat: %d\n", table->time_to_eat);
    printf("Time to sleep: %d\n", table->time_to_sleep);
    printf("Time to die: %d\n", table->time_to_die);
    printf("Max meals: %d\n", table->max_meals);
    printf("End: %d\n", table->end);
}

// Philo pointer*
void    print_philo(t_philo *philo)
{
    printf("Philo id: %d\n", philo->id);
    printf("Is dead: %d\n", philo->is_dead);
}

// Fork pointer*
void    print_fork(t_fork *fork)
{
    printf("Fork id: %d\n", fork->id);
}

void    print_all(t_table *table)
{
    int c;

    c =  0;
    printf("------------------------------\n");
    printf("TABLE:\n");
    print_table(table);
    printf("------------------------------\n");
    while (c < table->num_of_philos)
    {
        printf("----------------------\n");
        print_philo(&table->philos[c]);
        printf("\n");
        print_fork(&table->forks[c]);
        printf("----------------------\n");
        c++;
    }   
}