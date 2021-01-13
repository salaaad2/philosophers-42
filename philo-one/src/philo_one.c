#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "one_utils.h"
#include "philo_one.h"

static short
	ph_init(int ac, char *av[], t_philo *ph)
{
    int i;

    i = 1;
    while (i < ac)
    {
        if (!ph_isfullnum(av[i]))
            return (-1);
        else
        {
            ph_fills(ac, av, ph);
        }
        i++;
    }
    return (0);
}

static void*
	ph_act(void *ptr)
{
    t_philo *ph;

    ph = (t_philo*)ptr;
    printf("\n%d is in a thread\n", ph->num);
    return (ptr);
}

void
	ph_start(t_philo *ph)
{
    pthread_t pt;
    t_philo **pht;
    int i;

    i = 0;
    pht = malloc(sizeof(t_philo) * ph->max_ph);
    while (i < ph->max_ph)
    {
        pht[i] = malloc(sizeof(t_philo));
        i++;
    }
    i = 0;
    while (i < ph->max_ph)
    {
        pht[i]->num = i;
        pthread_create(&pt, NULL, ph_act, pht[i]);
        i++;
    }
    pthread_join(pt, NULL);
}

int
	main(int ac, char *av[])
{
    t_philo ph;

    if (ac <= 4 || ac >= 7)
    {
        ft_putstr("wrong number of arguments\n");
        return (1);
    }
    else
    {
        printf("[%d]\n", ph_atoi(av[2]));
        if (ph_init(ac, av, &ph) == -1)
            return (1);
        printf("[%d][%d][%d][%d][%d]", ph.max_ph, ph.time_to_die, ph.time_to_eat,
               ph.time_to_sleep, ph.appetite);
        ph_start(&ph);
    }
    return (0);
}
