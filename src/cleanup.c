/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:11:57 by danalmei          #+#    #+#             */
/*   Updated: 2024/01/16 15:12:18 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void end_simulation(t_table *table) {
    // Join philosopher threads
    for (int i = 0; i < table->num_of_philos; i++) {
        pthread_join(table->philos[i].philo, NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < table->num_of_philos; i++) {
        pthread_mutex_destroy(&table->forks[i].mtx);
    }

    // Free allocated memory
    free(table->philos);
    free(table->forks);
}
