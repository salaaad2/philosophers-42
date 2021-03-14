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

static void		*ph_check(t_philo *ph)
{
	int i;
	int j;

	while (1)
	{
		i = -1;
		j = 0;
		while (++i < ph[0].shared->max_ph)
		{
			if (!ph[i].apetite)
				j++;
			if (ph[i].apetite && ph[i].ttd >= 0 && ph_cmptime(ph[i].ttd))
			{
				ph_speak(ph_timest(), ph[i].num, PHILO_DEATH, ph[i].shared);
				ph_exit(ph);
			}
			if (j == ph[i].shared->max_ph)
			{
				ph_speak(ph_timest(), ph[i].num, PHILO_FULL, ph[i].shared);
				ph_exit(ph);
			}
		}
	}
	return (NULL);
}

static void		*ph_act(void *ptr)
{
	t_philo			*ph;

	ph = (t_philo*)ptr;
	while (ph->apetite != 0)
	{
		sem_wait(ph->shared->forks);
		ph_speak(ph_timest(), ph->num, PHILO_FORKT, ph->shared);
		sem_wait(ph->shared->forks);
		ph_speak(ph_timest(), ph->num, PHILO_FORKT, ph->shared);
		ph_speak(ph_timest(), ph->num, PHILO_EAT, ph->shared);
		ph->apetite -= 1;
		ph->ttd = ph_timest() + ph->shared->time_to_die;
		usleep(ph->shared->time_to_eat * 1000);
		sem_post(ph->shared->forks);
		sem_post(ph->shared->forks);
		ph_speak(ph_timest(), ph->num, PHILO_SLEEP, ph->shared);
		usleep(ph->shared->time_to_sleep * 1000);
		ph_speak(ph_timest(), ph->num, PHILO_THINK, ph->shared);
	}
	ph->ttd = -1;
	return (NULL);
}

void			ph_loop(t_philo *pht)
{
	pthread_t		pt[255];
	int				i;

	i = -1;
	while (++i < pht[0].shared->max_ph)
	{
		pthread_create(&pt[i], NULL, ph_act, &pht[i]);
		pthread_detach(pt[i]);
		pthread_join(pt[i], NULL);
	}
}

void			ph_start(t_shared *sh)
{
	sem_t			forks;
	sem_t			speaks;
	t_philo			pht[255];
	int				i;

	sh->forks = (sem_t*)&forks;
	sh->speaks = (sem_t*)&speaks;
	i = -1;
	while (++i < sh->max_ph)
	{
		pht[i] = ph_set(i, sh, pht[i]);
		pht[i].shared = sh;
	}
	ph_sem_init(sh, sh->max_ph);
	ph_loop(pht);
	ph_check(pht);
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
