#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "one_utils.h"
#include "one_actions.h"
#include "philo_one.h"

static void*
ph_check(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	while (1)
	{
		if (ph->isdead)
		{
			exit(1);
		}
	}
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
	pthread_mutex_t forks[*sh->max_ph];
	pthread_t pt;
	t_philo **pht;
	int i;

	i = 0;
	pht = (t_philo **)malloc((sizeof(t_philo*) * *sh->max_ph));
	sh->forks = (pthread_mutex_t**)&forks;
	while (i < *sh->max_ph)
	{
		pht[i] = (t_philo *)malloc(sizeof(t_philo));
		pht[i]->num = i + 1;
		pht[i]->shared = sh;
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < *sh->max_ph)
	{
		pht[i]->lfork = &forks[i];
		pht[i]->rfork = (i == (*sh->max_ph - 1)) ? &forks[0] :
            &forks[i + 1];
		printf("\n[%p][%p]%d\n", (void*)pht[i]->lfork, (void*)pht[i]->rfork, i);
		pthread_create(&pt, NULL, ph_act, pht[i]);
		pthread_create(&pt, NULL, ph_check, pht[i]);
		i++;
	}
	pthread_join(pt, NULL);
	/* pthread_mutex_destroy(pht[0]->lfork); */
	/* pthread_mutex_destroy(pht[1]->rfork); */
	/* ph_free(sh, pht); */
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
