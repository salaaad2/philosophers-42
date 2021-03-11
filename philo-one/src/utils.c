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

#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

short
	ph_free(t_shared *sh, t_philo **pht)
{
	int i;

	i = -1;
	while (++i < sh->max_ph)
	{
		free(pht[i]);
	}
	free(pht);
	exit(0);
	return (1);
}

int
	ph_atoi(char *str)
{
	int n;

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
	int i;

	i = -1;
	while (str[i])
		write(1, &str[++i], 1);
}

short
	ph_isfullnum(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] > 47 && str[i] < 58))
			return (0);
	}
	return (1);
}

long
	ph_timest(short status)
{
	struct timeval	tv;
	static long		ftime;
	long ct;

	gettimeofday(&tv, NULL);
	if (status == 0)
	{
		ftime = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	}
	ct = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return ((status == 0) ? ftime : ct - ftime);
}

short
	ph_fills(int ac, char *av[], t_shared *sh)
{
	sh->max_ph = ph_atoi(av[1]);
	sh->time_to_die = ph_atoi(av[2]);
	sh->time_to_eat = ph_atoi(av[3]);
	sh->time_to_sleep = ph_atoi(av[4]);
	sh->time = ph_timest(0);
	sh->isdead = 0;
	if (ac == 6)
		sh->apetite = ph_atoi(av[5]);
	else
		sh->apetite = -1;
	return (0);
}
