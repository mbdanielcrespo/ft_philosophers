#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

//number_of_philosophers die eat sleep
// 5 200 200 200 [5]
typedef struct s_fork
{
	int		id;
	t_mtx	mtx;
}	t_fork;

typedef struct s_philo
{
	int		id;
	int		status;
	long long	last_meal;
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
	long long	dinner_start;
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
	HUNGRY = 2,
	EATING = 3,
	SLEEPING = 4,
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
int has_died(t_philo *philo, char *debug);
int		philo_think(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
void	*philosopher_routine(void *arg);

// Init
void    init_table(t_table *table, char **av);
void	init_philos(t_table *table);
void	init_forks(t_table *table);
void	init_philos_threads(t_table *table);

// Time
long long	current_time_ms(void);
long long	elapsed_time_ms(long long start_time);
void		custom_sleep_ms(int ms);

#endif