#include <stdlib.h>
#include <stdio.h>

#include "one_utils.h"
#include "philo_one.h"

static void
	ph_fills(int ac, char *av[], t_philo *ph)
{
    ph->max_ph = ph_atoi(av[1]);
    ph->time_to_die = ph_atoi(av[2]);
    ph->time_to_eat = ph_atoi(av[3]);
    ph->time_to_sleep = ph_atoi(av[4]);
    if (ac == 6)
        ph->appetite = ph_atoi(av[5]);
}

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
    }
    return (0);
}
