#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>     // write usleep
#include <stdlib.h>     // malloc free
#include <stdio.h>      // printf
#include <pthread.h>    // mutex, threads
#include <sys/time.h>   // get_time_of_day
#include <limits.h>     // INT_MAX
#include <errno.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
// 5 200 200 200 [5]
typedef struct s_fork
{
	int		id;
	t_mtx	mtx;
}	t_fork;

typedef struct s_philo
{
	int		id;
	int		status;		//
	int		is_dead;
	t_fork	*left_fork;
	t_fork	*right_fork;
	pthread_t	philo;
	t_table	*table;
}	t_philo;

typedef	struct s_table
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_meals;		//-1 uninitialized
	int		end;
	t_philo	*philos;
	t_fork	*forks;
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

typedef	enum e_status
{
	THINKING = 1,
	EATING = 2,
	SLEEPING = 3,
}		t_status;

// Utils
int		is_digit(char ch);
int		is_space(char ch);
void    error_exit(char *error);
void    *safe_malloc(size_t bytes);
void	handle_mutex_error(int stat, t_opcode opcode);
void    safe_mutex_handle(t_mtx *mutex, t_opcode opcode);

// Parse
char	*valid_input(char *str);
int		ft_atol(char *str);
void	parse_input(t_table *table, char **av);

// Debug
void    print_all(t_table *table);
void    print_table(t_table *table);
void    print_philo(t_philo *philo);
void    print_fork(t_fork *fork);

// Dinner
void *philosopher_routine(void *arg);

// Init
void    init_table(t_table *table, char **av);
void	init_philos(t_table *table);
void	init_forks(t_table *table);

#endif