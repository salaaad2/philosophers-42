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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "utils.h"
#include "actions.h"
#include "philo.h"

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
