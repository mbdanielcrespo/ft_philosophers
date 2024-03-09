/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danalmei <danalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:52:16 by danalmei          #+#    #+#             */
/*   Updated: 2024/03/09 16:52:16 by danalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;
typedef struct s_fork
{
	int		id;
	t_mtx	mtx;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long long	last_meal;
	int			n_meals;
	int			is_dead;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	philo;
	t_table		*table;
}	t_philo;

typedef	struct s_table
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_meals;
	int		end;
	long long	dinner_start;
	pthread_t	monitor_thread;
	t_philo	*philos;
	t_fork	*forks;
	t_mtx	mtx;
	t_mtx	log;
}	t_table;


typedef enum e_opcode
{
	LOCK = 0,
	UNLOCK = 1,
	INIT = 2,
	DESTROY = 3,
	CREATE = 4,
	JOIN = 5,
	DETEACH = 6,
}		t_opcode;

// Parse
int		is_valid_input(char *str);
int		ft_atol(char *str);
int		parse_input(t_table *table, char **av);

// Init
int		init_table(t_table *table);
void	init_philos(t_table *table);
void	init_forks(t_table *table);
int		init_threads(t_table *table);

// Dinner
int		philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	*philosopher_routine(void *arg);

// Forks
void	take_fork(t_philo *philo, t_fork *taken_fork);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);

// Cleanup
void    join_threads(t_table *table);
void    destroy_mutexes(t_table *table);
void    destroy_structures(t_table *table);
void    end_simulation(t_table *table);

// Time
long long	current_time_ms(void);
long long	elapsed_time_ms(long long start_time);
int			custom_wait(int wait_ms, t_philo *philo, int action);
int			has_philo_died(t_philo *philo);

// Utils
int		is_digit(char ch);
int		is_space(char ch);
void	increase_meal_counter(t_philo *philo);
void	write_text(char *text, t_philo *philo);
void    mutex_handle(t_mtx *mutex, t_opcode opcode);

// Debug
void    print_all(t_table *table);
void    print_table(t_table *table);
void    print_philo(t_philo *philo);
void    print_fork(t_fork *fork);

#endif