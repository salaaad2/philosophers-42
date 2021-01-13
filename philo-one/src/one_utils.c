#include "one_utils.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

int
	ph_atoi(char *str)
{
    int n;

    n = 0;
    if (*str == 0)
        return (0);
    while (*str)
        n = n * 10 + (*str++ - 48);
    return (n);
}

void
	ft_putstr(char *str)
{
    int i;

    i = -1;
    while (str[i])
    {
        write(1, &str[++i], 1);
    }
}

short
	ph_isfullnum(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (!(str[i] > 47 && str[i] < 58))
            return (0);
    }
    return (1);
}

long
	ph_timest(short status, long ct)
{
    struct timeval tv;
    static long ftime;

    gettimeofday(&tv, NULL);
    ftime = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    return ((status == 0) ? ftime : ct - ftime);
}

void
	ph_fills(int ac, char *av[], t_philo *ph)
{
    ph->max_ph = ph_atoi(av[1]);
    ph->time_to_die = ph_atoi(av[2]);
    ph->time_to_eat = ph_atoi(av[3]);
    ph->time_to_sleep = ph_atoi(av[4]);
    ph->time = ph_timest(0, 0);
    printf("[%ld]", ph->time);
    if (ac == 6)
        ph->appetite = ph_atoi(av[5]);
}
