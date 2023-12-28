#include "philo.h"

void    set_flag(t_mtx *mutex, int *dest, int value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

int    get_flag(t_mtx *mutex, int *value)
{
    int ret;

    safe_mutex_handle(mutex, LOCK);
    ret = value;
    safe_mutex_handle(mutex, UNLOCK);
    return(ret);
}

long    get_long(t_mtx *mutex, long *value)
{
    long ret;

    safe_mutex_handle(mutex, LOCK);
    ret = value;
    safe_mutex_handle(mutex, UNLOCK);
    return(ret);
}

void    set_long(t_mtx *mutex, long *dest, long value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

int simulation_end(t_table *table)
{
    return (get_flag(table->table_mutex, &table->end));
}

