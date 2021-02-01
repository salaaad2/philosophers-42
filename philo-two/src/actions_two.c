#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#include "utils_two.h"
#include "actions_two.h"
#include "philo_two.h"

short
ph_eat(t_philo *ph)
{
    struct timeval ctv;

    gettimeofday(&ctv, NULL);
    if ((ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)) - ph->lastate) > *ph->shared->time_to_die ||
        ph->shared->isdead == 1)
    {
        ph->isdead = 1;
        return (1);
    }
    gettimeofday(&ctv, NULL);
    sem_wait(ph->shared->forks[ph->num]);
    printf("\n[%ld]%d is eating", ph_timest(1, (ctv.tv_sec * 1000) +
    usleep(*ph->shared->time_to_eat * 1000)), ph->num);
    ph->lastate = ph_timest(1, (ctv.tv_sec * 1000) +
                            (ctv.tv_usec / 1000));
    sem_wait(ph->shared->forks[ph->num]);
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
    gettimeofday(&ctv, NULL);
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
