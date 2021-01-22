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

    pthread_mutex_lock(ph->lfork); /* SEGV */
    pthread_mutex_lock(ph->rfork); /* SEGV */
    printf("\n[%ld]%d is eating", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    gettimeofday(&ctv, NULL);
    if ((ph_timest(1, ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000))) - ph->lastate)  > *ph->shared->time_to_die)
    {
        ph->shared->isdead = 1;
        pthread_mutex_unlock(ph->lfork);
        pthread_mutex_unlock(ph->rfork); /* SEGV */
        return (-1);
    }
    else
    {
        ph->lastate = ph_timest(1, (ctv.tv_sec * 1000) +
                                (ctv.tv_usec / 1000));
    }
    usleep(*ph->shared->time_to_eat);
    printf("\n[%ld][no %d] stopped eating", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    pthread_mutex_unlock(ph->lfork);
    pthread_mutex_unlock(ph->rfork); /* SEGV */
    return (0);
}


short
ph_sleep(t_philo *ph)
{
    struct timeval ctv;

    ph->issleeping = 1;
    gettimeofday(&ctv, NULL);
    printf("\n[%ld]%d is now sleeping", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    usleep(*ph->shared->time_to_sleep);
    ph->issleeping = 0;
    return (0);
}

short
ph_think(t_philo *ph)
{
    struct timeval ctv;

    ph->isthinking = 1;
    gettimeofday(&ctv, NULL);
    printf("\n[%ld]%d is now thinking", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    return (0);
}
