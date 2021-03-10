/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoenne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:53:01 by fmoenne-          #+#    #+#             */
/*   Updated: 2021/03/02 14:53:52 by fmoenne-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#include "utils.h"
#include "actions.h"
#include "philo.h"

static void*
	ph_check(void *ptr)
{
	t_philo			*ph;
	struct timeval	ctv;

	ph = (t_philo*)ptr;
	while (ph->shared->isdead == 0)
	{
		if (ph->isdead && ph->shared->isdead == 0)
		{
			gettimeofday(&ctv, NULL);
			sem_wait(ph->shared->speaks);
			ph->shared->isdead = 1;
			return (NULL);
		}
		else if (ph->shared->apetite == 0)
		{
			gettimeofday(&ctv, NULL);
			ph_speak(ph_timest(1), ph->num, PHILO_FULL, ph->shared);
			sem_wait(ph->shared->speaks);
			return (NULL);
		}
	}
	return (NULL);
}

int
ph_lock(t_philo * ph, unsigned int ttw)
{
	struct timeval ct;
	struct timeval lock_start;

	gettimeofday(&ct, NULL);
	gettimeofday(&lock_start, NULL);
	while ((((ct.tv_sec * 1000) + (ct.tv_usec / 1000)) -
			((lock_start.tv_sec * 1000) + (lock_start.tv_usec / 1000))) < ttw)
	{
		gettimeofday(&ct, NULL);
		if ((((ct.tv_sec * 1000) + (ct.tv_usec / 1000)) -
			 ((lock_start.tv_sec * 1000) + (lock_start.tv_usec / 1000))) >= ph->shared->time_to_die)
		{
			ph->isdead = 1;
			return (1);
		}
	}
	return (0);
}

static void*
	ph_act(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	while (1)
	{
		sem_wait(ph->shared->forks);
		ph_speak(ph_timest(1), ph->num, PHILO_FORKT, ph->shared);
		sem_wait(ph->shared->forks);
		ph_speak(ph_timest(1), ph->num, PHILO_FORKT, ph->shared);
		ph_speak(ph_timest(1), ph->num, PHILO_EAT, ph->shared);
		ph->lastate = ph_timest(1);
		if (ph->apetite >= 0 && ph_lock(ph, ph->shared->time_to_eat) == 1)
		{
			ph_speak(ph_timest(1), ph->num, PHILO_DEATH, ph->shared);
			break;
		}
		if (ph->apetite >= 0 && ph->shared->apetite != -1)
		{
			ph->apetite -= 1;
			ph->shared->apetite -= 1;
			if (ph->shared->apetite == 0)
			{
				break;
			}
		}
		sem_post(ph->shared->forks);
		ph_speak(ph_timest(1), ph->num, PHILO_FORKP, ph->shared);
		sem_post(ph->shared->forks);
		ph_speak(ph_timest(1), ph->num, PHILO_FORKP, ph->shared);
		ph_speak(ph_timest(1), ph->num, PHILO_SLEEP, ph->shared);
		if (ph_lock(ph, ph->shared->time_to_sleep) == 1)
		{
			ph_speak(ph_timest(1), ph->num, PHILO_DEATH, ph->shared);
			break;
		}
		ph_speak(ph_timest(1), ph->num, PHILO_THINK, ph->shared);
	}
	return (ptr);
}

void
	ph_start(t_shared *sh)
{
	sem_t	forks;
	sem_t	speaks;
	pthread_t		pt;
	t_philo			**pht;
	int				i;

	if (!(pht = (t_philo **)malloc((sizeof(t_philo*) * sh->max_ph))))
		return ;
	sh->forks = (sem_t*)&forks;
	sh->speaks = (sem_t*)&speaks;
	i = -1;
	while (++i < sh->max_ph)
	{
		pht[i] = (t_philo *)malloc(sizeof(t_philo));
		pht[i]->num = i + 1;
		pht[i]->isdead = 0;
		pht[i]->lastate = 0;
		if (sh->apetite != -1)
			pht[i]->apetite = sh->apetite;
		else
			pht[i]->apetite = -1;
		pht[i]->shared = sh;
	}
	ph_sem_init(sh, sh->max_ph);
	if (sh->apetite != -1)
		sh->apetite *= sh->max_ph;
	printf("%d\n", sh->apetite);
	i = -1;
	while (++i < sh->max_ph && sh->isdead == 0)
	{
		if ((sh->pid = fork()) == 0)
		{
			pthread_create(&pt, NULL, ph_act, pht[i]);
			pthread_create(&pt, NULL, ph_check, pht[i]);
		}
	}
	pthread_join(pt, NULL);
	ph_free(sh, pht);
}

int
	main(int ac, char *av[])
{
	t_shared sh;
	int i;

	i = 1;
	if (ac <= 4 || ac >= 7)
	{
		ft_putstr("wrong number of arguments\n");
		return (1);
	}
	else
	{
		while (i < ac)
		{
			if (!ph_isfullnum(av[i]))
				return (-1);
			i++;
		}
		ph_fills(ac, av, &sh);
		ph_start(&sh);
	}
	return (0);
}
