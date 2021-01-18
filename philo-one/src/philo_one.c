#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

#include "one_utils.h"
#include "philo_one.h"

static void*
	ph_act(void *ptr)
{
    t_philo *ph;
    struct timeval ctv;

    ph = (t_philo*)ptr;
    pthread_mutex_lock(&ph->shared->pmt);
    gettimeofday(&ctv, NULL);
    printf("\n[%ld]%d is in a thread, he will eat for [%d] milliseconds soon", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num, *ph->shared->time_to_eat);
    ph->hasfork += 2;
    ph->iseating = 1;
    usleep(*ph->shared->time_to_eat);
    printf("\n[%ld]%d is eating", ph_timest(1, (ctv.tv_sec * 1000) +
        (ctv.tv_usec / 1000)), ph->num);
    ph->hasfork -= 2;
    ph->iseating = 0;
    pthread_mutex_unlock(&ph->shared->pmt);
    return (ptr);
}

void
	ph_start(t_shared *sh)
{
    pthread_t pt;
    t_philo **pht;
    int i;

    i = 0;
    pht = (t_philo **)malloc((sizeof(t_philo*) * *sh->max_ph));
    while (i <= *sh->max_ph)
    {
        pht[i] = malloc(sizeof(t_philo));
        pht[i]->num = i + 1;
        pht[i]->shared = sh;
        i++;
    }
    i = 0;
    if (pthread_mutex_init(&sh->pmt, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return ;
    }
    while (i < *sh->max_ph)
    {
        pthread_create(&pt, NULL, ph_act, pht[i]);
        i++;
    }
    pthread_join(pt, NULL);
    pthread_mutex_destroy(&sh->pmt);
}

static short
	ph_init(int ac, char *av[], t_shared *sh)
{
    int i;

    i = 1;
    while (i < ac)
    {
        if (!ph_isfullnum(av[i]))
            return (-1);
        i++;
    }
    ph_fills(ac, av, sh);
    return (0);
}

int
	main(int ac, char *av[])
{
    t_shared sh;

    if (ac <= 4 || ac >= 7)
    {
        ft_putstr("wrong number of arguments\n");
        return (1);
    }
    else
    {
        printf("[%d]\n", ph_atoi(av[2]));
        if (ph_init(ac, av, &sh) == -1)
            return (1);
        ph_start(&sh);
    }
    return (0);
}
