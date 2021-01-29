#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#include "one_utils.h"
#include "one_actions.h"
#include "philo_one.h"

short
ph_eat(t_philo *ph)
{
    struct timeval ctv;

    gettimeofday(&ctv, NULL);
    if ((ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)) - ph->lastate) > *ph->shared->time_to_die)
    {
        ph->isdead = 1;
        return (1);
    }
    if (*ph->shared->appetite != -1 && ph->shared->isdead == 0)
        ph->ate++;
    if (ph->ate == *ph->shared->appetite)
        ph->isfull = 1;
    pthread_mutex_lock(ph->lfork);
    pthread_mutex_lock(ph->rfork);
    gettimeofday(&ctv, NULL);
    printf("\n[%ld]%d is eating", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    usleep(*ph->shared->time_to_eat * 1000);
    ph->lastate = ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000));
    pthread_mutex_unlock(ph->lfork);
    pthread_mutex_unlock(ph->rfork);
    return (0);
}


short
ph_sleep(t_philo *ph)
{
    struct timeval ctv;

    gettimeofday(&ctv, NULL);
    printf("\n[%ld]%d is sleeping", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    usleep(*ph->shared->time_to_sleep * 1000);
    return (0);
}

short
ph_think(t_philo *ph)
{
    struct timeval ctv;

    gettimeofday(&ctv, NULL);
    printf("\n[%ld]%d is thinking", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    return (0);
}
