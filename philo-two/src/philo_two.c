#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/wait.h>

#include "utils.h"
#include "actions.h"
#include "philo_two.h"

static void*
	ph_check(void *ptr)
{
	t_philo			*ph;
	struct timeval	ctv;

	ph = (t_philo*)ptr;
	while (ph->shared->isdead == 0)
	{
		if (ph->isdead)
		{
			gettimeofday(&ctv, NULL);
			ph_speak(ph_timest(1, (ctv.tv_sec * 1000) +
				(ctv.tv_usec / 1000)), ph->num, PHILO_DEATH, ph->shared);
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
	sem_t	forks;
	pthread_t		pt;
	t_philo			**pht;
	int				i;

	if (!(pht = (t_philo **)malloc((sizeof(t_philo*) * *sh->max_ph))))
		return ;
	sh->forks = (sem_t*)&forks;
	i = -1;
	while (++i < *sh->max_ph)
	{
		pht[i] = (t_philo *)malloc(sizeof(t_philo));
		pht[i]->num = i + 1;
		pht[i]->isdead = 0;
		pht[i]->lastate = 0;
		if (*sh->appetite != -1)
			pht[i]->ate = 0;
		pht[i]->shared = sh;
	}
	ph_sem_init(sh, *sh->max_ph);
	i = -1;
	while (++i < *sh->max_ph && sh->isdead == 0)
	{
		printf("qweqweqwe\n");
		pthread_create(&pt, NULL, ph_act, pht[i]);
		pthread_create(&pt, NULL, ph_check, pht[i]);
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
		if (ph_init(ac, av, &sh) == -1)
			return (1);
		ph_start(&sh);
	}
	return (0);
}
