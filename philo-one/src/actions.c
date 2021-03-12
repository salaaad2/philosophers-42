/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoenne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:53:24 by fmoenne-          #+#    #+#             */
/*   Updated: 2021/03/02 14:53:50 by fmoenne-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include "actions.h"

short		ph_speak(long ts, int nb, char *message, t_shared *sh)
{
	pthread_mutex_lock(&sh->speaks);
	if (sh->isdead == 1 || sh->allfull == 1)
	{
		pthread_mutex_lock(&sh->speaks);
		return (1);
	}
	dprintf(1, "%lu %d %s", ts, nb, message);
	pthread_mutex_unlock(&sh->speaks);
	return (0);
}

long		ph_timest(short status)
{
	struct timeval	tv;
	static long		ftime;
	long			ct;

	gettimeofday(&tv, NULL);
	if (status == 0)
	{
		ftime = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	}
	ct = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return ((status == 0) ? ftime : ct - ftime);
}

t_philo		ph_set(int i, t_shared *sh, t_philo ph)
{
	ph.num = i + 1;
	ph.isdead = 0;
	ph.lastate = 0;
	if (sh->apetite != -1)
		ph.apetite = sh->apetite;
	else
		ph.apetite = -1;
	ph.shared = sh;
	if (i == 0 && sh->apetite != -1)
		sh->apetite *= sh->max_ph;
	return (ph);
}
