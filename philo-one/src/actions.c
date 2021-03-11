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

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#include "actions.h"

short
	ph_speak(long ts, int nb, char *message, t_shared *sh)
{
	pthread_mutex_lock(&sh->speaks);
	if (sh->isdead == 1 || sh->apetite == 0)
	{
		pthread_mutex_unlock(&sh->speaks);
		return (1);
	}
	printf("%ld %d %s\n", ts, nb, message);
	pthread_mutex_unlock(&sh->speaks);
	return (0);
}

long
	ph_timest(short status)
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
