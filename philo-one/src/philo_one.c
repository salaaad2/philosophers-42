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

    gettimeofday(&ctv, NULL);
    ph = (t_philo*)ptr;
    printf("\n[%ld]%d is in a thread", ph_timest(1, (ctv.tv_sec * 1000) + (ctv.tv_usec / 1000)), ph->num);
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
    while (i < *sh->max_ph)
    {
        pthread_create(&pt, NULL, ph_act, pht[i]);
        i++;
    }
    pthread_join(pt, NULL);
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
