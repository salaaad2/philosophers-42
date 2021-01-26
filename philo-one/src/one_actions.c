#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
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
    printf("\n[%ld]%d is waiting for mutex to be unlocked", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    pthread_mutex_lock(ph->lfork);
    pthread_mutex_lock(ph->rfork);
    gettimeofday(&ctv, NULL);
    printf("\n[%ld]%d is eating", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    ph->lastate = ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000));
    usleep(*ph->shared->time_to_eat);
    pthread_mutex_unlock(ph->lfork);
    pthread_mutex_unlock(ph->rfork);
    printf("\n[%ld]%d stopped eating", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    return (0);
}


short
ph_sleep(t_philo *ph)
{
    struct timeval ctv;

    gettimeofday(&ctv, NULL);
    printf("\n[%ld]%d is now sleeping", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    usleep(*ph->shared->time_to_sleep);
    return (0);
}

short
ph_think(t_philo *ph)
{
    struct timeval ctv;

    gettimeofday(&ctv, NULL);
    printf("\n[%ld]%d is now thinking", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    return (0);
}
