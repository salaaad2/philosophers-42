#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#include "utils_two.h"
#include "actions_two.h"
#include "philo_two.h"
#include "sem_two.h"

static void*
ph_check(void *ptr)
{
	t_philo *ph;
    struct timeval ctv;

	ph = (t_philo*)ptr;
	while (1)
	{
		if (ph->isdead)
		{
			gettimeofday(&ctv, NULL);
			printf("\n[%ld]%d died", ph_timest(1, (ctv.tv_sec * 1000) +
				(ctv.tv_usec / 1000)), ph->num);
			ph->shared->isdead = 1;
			return (NULL);
		}
	}
	return (NULL);
}

static void*
ph_act(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	while (1)
	{
		ph_eat(ph);
		ph_sleep(ph);
		ph_think(ph);
	}
	return (ptr);
}

void
ph_start(t_shared *sh)
{
	sem_t forks[*sh->max_ph];
	pthread_t pt;
	t_philo **pht;
	int i;

	i = 0;
	pht = (t_philo **)malloc((sizeof(t_philo*) * *sh->max_ph));
	sh->forks = (sem_t**)&forks;
	while (i < *sh->max_ph)
	{
		pht[i] = (t_philo *)malloc(sizeof(t_philo));
		pht[i]->num = i + 1;
		pht[i]->shared = sh;
		pht[i]->isdead = 0;
		pht[i]->lastate = 0;
		ph_open_sem(i, *sh->max_ph);
		i++;
	}
	i = 0;
	while (i < *sh->max_ph && sh->isdead == 0)
	{
		pthread_create(&pt, NULL, ph_act, pht[i]);
		pthread_create(&pt, NULL, ph_check, pht[i]);
		i++;
	}
	pthread_join(pt, NULL);
	ph_free(sh, pht);
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
	ph_fills(av, sh);
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
