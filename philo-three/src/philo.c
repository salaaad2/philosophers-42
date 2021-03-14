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
#include <signal.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils.h"
#include "actions.h"
#include "philo.h"

static void		*ph_check(t_philo *ph)
{
	int i;
	int status;
	pid_t pid;

	pid = -1;
	status = 0;
	while (!status && pid <= 0)
		pid = waitpid(-1, &status, 0);
	if (WEXITSTATUS(status))
	{
		i = -1;
		while (++i < ph[0].shared->max_ph)
		{
			if (pid != ph[i].pid)
				kill(ph[i].pid, SIGKILL);
			else
			{
				ph_speak(ph_timest(), ph[i].num, PHILO_DEATH, ph[i].shared);
			}
		}
	}
	else
		ph_speak(ph_timest(), ph[0].num, PHILO_FULL, ph[0].shared);
	return (NULL);
}

void	*ph_fork(void *ptr)
{
	t_philo *ph;

	ph = (t_philo*)ptr;
	while (1)
		if (ph_cmptime(ph->ttd))
			exit(0);
	return (NULL);
}

static void		*ph_act(t_philo *ph)
{
	pthread_t p;

	pthread_create(&p, NULL, ph_fork, ph);
	pthread_detach(p);
	pthread_join(p, NULL);
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
	exit(0);
	return (NULL);
}

static void		ph_loop(t_philo *pht)
{
	int				i;

	i = -1;
	while (++i < pht[0].shared->max_ph)
	{
		pht[i].pid = fork();
		if (pht[i].pid == 0)
			ph_act(&pht[i]);
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
	}
	ph_sem_init(sh, sh->max_ph);
	ph_loop(pht);
	ph_check(pht);
	exit(0);
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
