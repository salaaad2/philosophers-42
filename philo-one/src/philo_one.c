#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "one_utils.h"
#include "one_actions.h"
#include "philo_one.h"

static void*
ph_act(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	ph_eat(ph);
	ph_sleep(ph);
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
	while (i < *sh->max_ph)
	{
		pht[i] = (t_philo *)malloc(sizeof(t_philo));
		pht[i]->lfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		/* pht[i]->rfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)); */
		pht[i]->num = i + 1;
		pht[i]->shared = sh;
		i++;
	}
	i = 0;
	while (i < *sh->max_ph)
	{
        printf("[%d]", i);
		pthread_mutex_init(pht[i]->lfork, NULL);
		pht[i]->lfork = pht[i]->shared->forks[i];
		/* pthread_mutex_init(pht[i]->rfork, NULL); */
		/* pht[i]->rfork = (i == (*sh->max_ph - 1)) ? pht[i]->shared->forks[0] : */
        /*     pht[i]->shared->forks[i + 1]; */
		pthread_create(&pt, NULL, ph_act, pht[i]);
		i++;
	}
	pthread_join(pt, NULL);
	pthread_mutex_destroy(pht[0]->lfork);
	/* pthread_mutex_destroy(pht[i]->rfork); */
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
	if (!(sh->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t*)* *sh->max_ph)))
		return (-1);
    while (i < *sh->max_ph)
    {
        if ((!(sh->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)))))
            return (-1);
        i++;
	}
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
