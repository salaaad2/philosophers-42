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

short	ph_speak(long ts, int nb, char *message, t_shared *sh)
{
	pthread_mutex_lock(&sh->speaks);
	printf("%lu %d %s", ts - sh->time, nb, message);
	pthread_mutex_unlock(&sh->speaks);
	return (0);
}

long	ph_timest(void)
{
	struct timeval	tv;
	long			ct;

	gettimeofday(&tv, NULL);
	ct = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (ct);
}

long	ph_cmptime(long time)
{
	return (time < ph_timest());
}

t_philo	ph_set(int i, t_shared *sh, t_philo ph)
{
	ph.num = i + 1;
	ph.isdead = 0;
	ph.lastate = 0;
	ph.ttd = sh->time_to_die + ph_timest();
	if (sh->apetite != -1)
		ph.apetite = sh->apetite;
	else
		ph.apetite = -1;
	ph.shared = sh;
	return (ph);
}
