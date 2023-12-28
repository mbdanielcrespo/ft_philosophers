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

typedef struct s_fork
{
	int		fork_id;
	t_mtx	fork;
}   			t_fork;

// ./philo 5 800 200 200
typedef struct s_philo
{
	int     philo_id;
	int     nbr_meals;
	int		is_full;
	long	last_meal_time;
	t_fork  *first_fork;
	t_fork  *second_fork;
	pthread_t	thread_id;
	t_table		*table;
	int		all_threads_sync;
}   			t_philo;

// ./philo 5 800 200 200 
typedef	struct s_table
{
	int	philo_nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;	// [5] | flag if -1
	int	meals_limit;
	int	start;
	int	end;			//philosopher dies or all are full
	t_fork	*forks;		//arr of forks
	t_philo	*philos;	//arr of philos
	t_mtx	table_mutex;
} t_table;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETEACH,
}		t_opcode;

void    error_exit(char *error);
void    *safe_malloc(size_t bytes);
void    parse_input(t_table *table, char **av);
void    safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void    data_init(t_table *table);

#endif