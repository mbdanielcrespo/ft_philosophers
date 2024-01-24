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
	pthread_t	monitor_thread;
	t_philo	*philos;
	t_fork	*forks;
	t_mtx	mtx;
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

// Utils
int		is_digit(char ch);
int		is_space(char ch);
//void	*safe_malloc(size_t bytes);
//void	error_exit(char *error)
void    mutex_handle(t_mtx *mutex, t_opcode opcode);

// Parse
char	*valid_input(char *str);
int		ft_atol(char *str);
int		parse_input(t_table *table, char **av);

// Debug
void    print_all(t_table *table);
void    print_table(t_table *table);
void    print_philo(t_philo *philo);
void    print_fork(t_fork *fork);

// Dinner
int		even_philo_eat(t_philo *philo);
int		uneven_philo_eat(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_think(t_philo *philo);
int		philo_sleep(t_philo *philo);
void	*philosopher_routine(void *arg);

// Init
int		init_table(t_table *table, char **av);
void	init_philos(t_table *table);
void	init_forks(t_table *table);
int		init_threads(t_table *table);

// Time
long long	current_time_ms(void);
long long	elapsed_time_ms(long long start_time);
void		custom_wait(int wait_ms);

// Cleanup
void    join_threads(t_table *table);
void    destroy_mutexes(t_table *table);
void    destroy_structures(t_table *table);
void    end_simulation(t_table *table);


// Monitor
int		has_died(t_philo *philo);
int		has_someone_died(t_philo *philo);
void	*monitor_routine(void *arg);
#endif