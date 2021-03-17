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

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include "utils.h"
#include "actions.h"
#include "philo.h"

static void	ph_check(t_philo *ph)
{
	int		i;
	int		j;
	bool qwe = false;

	while (!qwe)
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
				pthread_mutex_lock(&ph->shared->speaks);
				ph_exit(ph);
				qwe = true;
				break ;
			}
			if (j == ph[i].shared->max_ph)
			{
				ph_speak(ph_timest(), ph[i].num, PHILO_FULL, ph[i].shared);
				pthread_mutex_lock(&ph->shared->speaks);
				ph_exit(ph);
				qwe = true;
				break ;
			}
		}
	}
}

static void	*ph_act(void *ptr)
{
	t_philo			*ph;

	ph = (t_philo*)ptr;
	while (ph->apetite != 0)
	{
		pthread_mutex_lock(ph->lfork);
		ph_speak(ph_timest(), ph->num, PHILO_FORKT, ph->shared);
		pthread_mutex_lock(ph->rfork);
		ph_speak(ph_timest(), ph->num, PHILO_FORKT, ph->shared);
		ph_speak(ph_timest(), ph->num, PHILO_EAT, ph->shared);
		ph->apetite -= 1;
		ph->ttd = ph_timest() + ph->shared->time_to_die;
		usleep(ph->shared->time_to_eat * 1000);
		pthread_mutex_unlock(ph->lfork);
		pthread_mutex_unlock(ph->rfork);
		ph_speak(ph_timest(), ph->num, PHILO_SLEEP, ph->shared);
		usleep(ph->shared->time_to_sleep * 1000);
		ph_speak(ph_timest(), ph->num, PHILO_THINK, ph->shared);
	}
	ph->ttd = -1;
	return (NULL);
}

void	ph_loop(t_philo *pht)
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

void	ph_start(t_shared *sh)
{
	pthread_mutex_t	forks[255];
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
		{
			if (i == (sh->max_ph - 1))
				pht[i].rfork = &forks[0];
			else
				pht[i].rfork = &forks[i + 1];
		}
		else
			pht[i].rfork = &forks[i + 1];
	}
	pthread_mutex_init(&sh->speaks, NULL);
	ph_loop(pht);
	ph_check(pht);
}

int	main(int ac, char *av[])
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
		if (ph_fills(ac, av, &sh) == -1)
		{
			dprintf(1, "invalid argument(s)\n");
			return (1);
		}
		ph_start(&sh);
	}
	return (0);
}
