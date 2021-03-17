/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoenne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:53:36 by fmoenne-          #+#    #+#             */
/*   Updated: 2021/03/02 14:54:01 by fmoenne-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "actions.h"
#include "utils.h"

void
	ph_exit(t_philo *pht)
{
	sem_unlink(PHILO_SEMF);
	sem_close(pht->shared->forks);
	sem_unlink(PHILO_SEMS);
	sem_close(pht->shared->speaks);
	exit(EXIT_SUCCESS);
}

int
	ph_atoi(char *str)
{
	int	n;

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
	int	i;

	i = -1;
	while (str[i])
		write(1, &str[++i], 1);
}

short
	ph_isfullnum(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] > 47 && str[i] < 58))
			return (0);
	}
	return (1);
}

short
	ph_fills(int ac, char *av[], t_shared *sh)
{
	sh->max_ph = ph_atoi(av[1]);
	sh->time_to_die = ph_atoi(av[2]);
	sh->time_to_eat = ph_atoi(av[3]);
	sh->time_to_sleep = ph_atoi(av[4]);
	sh->time = ph_timest();
	sh->isdead = 0;
	if (ac == 6)
		sh->apetite = ph_atoi(av[5]);
	else
		sh->apetite = -1;
	if ((sh->max_ph == 0) ||
		 (sh->time_to_die == 0) ||
		 (sh->time_to_eat == 0) ||
		 (sh->time_to_sleep == 0))
		return (-1);
	return (0);
}
