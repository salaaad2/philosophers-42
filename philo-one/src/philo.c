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

static void		*ph_check(void *ptr)
{
	t_philo			*ph;

	ph = (t_philo*)ptr;
	while (ph->shared->isdead == 0)
	{
		if (ph->isdead && ph->shared->isdead == 0)
		{
			ph_speak(ph_timest(1), ph->num, PHILO_DEATH, ph->shared);
			ph->shared->isdead = 1;
			pthread_mutex_lock(&ph->shared->speaks);
			return (NULL);
		}
		else if (ph->shared->apetite == 0)
		{
			ph_speak(ph_timest(1), ph->num, PHILO_FULL, ph->shared);
			pthread_mutex_lock(&ph->shared->speaks);
			return (NULL);
		}
	}
	return (NULL);
}

int				ph_lock(int mode, t_philo *ph, unsigned int ttw)
{
	struct timeval	ct;
	struct timeval	lock_start;
	long ttd;

	gettimeofday(&ct, NULL);
	gettimeofday(&lock_start, NULL);
	if (mode == 1)
	{
		ttd = ph->shared->time_to_die - ph->shared->time_to_eat;
	}
	else 
		ttd = ph->shared->time_to_die;
	while ((((ct.tv_sec * 1000) + (ct.tv_usec / 1000)) -
			((lock_start.tv_sec * 1000) + (lock_start.tv_usec / 1000))) < ttw)
	{
		gettimeofday(&ct, NULL);
		if ((((ct.tv_sec * 1000) + (ct.tv_usec / 1000)) -
			((lock_start.tv_sec * 1000) + (lock_start.tv_usec / 1000))) >=
			ttd)
		{
			ph->isdead = 1;
			return (1);
		}
	}
	return (0);
}

void
	ph_fork(int mode, t_philo *ph)
{
	if (mode == 1)
	{
		pthread_mutex_lock(ph->lfork);
		ph_speak(ph_timest(1), ph->num, PHILO_FORKT, ph->shared);
		pthread_mutex_lock(ph->rfork);
		ph_speak(ph_timest(1), ph->num, PHILO_FORKT, ph->shared);
		ph_speak(ph_timest(1), ph->num, PHILO_EAT, ph->shared);
		ph->lastate = ph_timest(1);
	}
	else
	{
		pthread_mutex_unlock(ph->lfork);
		ph_speak(ph_timest(1), ph->num, PHILO_FORKP, ph->shared);
		pthread_mutex_unlock(ph->rfork);
		ph_speak(ph_timest(1), ph->num, PHILO_FORKP, ph->shared);
		ph_speak(ph_timest(1), ph->num, PHILO_SLEEP, ph->shared);
	}
}

static void		*ph_act(void *ptr)
{
	t_philo			*ph;

	ph = (t_philo*)ptr;
	while (ph->shared->isdead == 0)
	{
		if (ph->shared->isdead == 0)
			ph_fork(1, ph);
		else
			break ;
		if (ph_lock(0, ph, ph->shared->time_to_eat) == 1)
			break ;
		if (ph->apetite >= 0 && ph->shared->apetite != -1)
		{
			ph->apetite -= 1;
			ph->shared->apetite -= 1;
			if (ph->shared->apetite == 0)
				break ;
		}
		if (ph->shared->isdead == 0)
			ph_fork(2, ph);
		else
			break ;
		if (ph_lock(1, ph, ph->shared->time_to_sleep) == 1)
			break ;
		ph_speak(ph_timest(1), ph->num, PHILO_THINK, ph->shared);
	}
	return (ptr);
}

void			ph_start(t_shared *sh)
{
	pthread_mutex_t	forks[255];
	pthread_t		pt;
	t_philo			pht[255];
	int				i;

	sh->forks = (pthread_mutex_t**)&forks;
	i = -1;
	while (++i < sh->max_ph)
	{
		pht[i] = ph_set(i, sh, pht[i]);
		pthread_mutex_init(&forks[i], NULL);
		pht[i].lfork = &forks[i];
		if (sh->max_ph != 1 && sh->max_ph != 2)
			pht[i].rfork = (i == (sh->max_ph - 1)) ? &forks[0] : &forks[i + 1];
		else
		{
			pht[i].rfork = &forks[i + 1];
		}
	}
	pthread_mutex_init(&sh->speaks, NULL);
	i = -1;
	while (++i < sh->max_ph && sh->isdead == 0)
	{
		pthread_create(&pt, NULL, ph_act, &pht[i]);
		pthread_create(&pt, NULL, ph_check, &pht[i]);
	}
	pthread_join(pt, NULL);
}

int				main(int ac, char *av[])
{
	t_shared		sh;
	int				i;

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
