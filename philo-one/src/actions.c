#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#include "utils.h"
#include "actions.h"
#include "philo_one.h"

short
	ph_speak(long ts, int nb, char *message, t_shared *sh)
{
	pthread_mutex_lock(&sh->speaks);
	printf("[%ld]%d %s\n", ts, nb, message);
	pthread_mutex_unlock(&sh->speaks);
	return (1);
}

short
	ph_eat(t_philo *ph)
{
	struct timeval ctv;

	gettimeofday(&ctv, NULL);
	if ((ph_timest(1, (ctv.tv_sec * 1000) +
					(ctv.tv_usec / 1000)) -
				ph->lastate) > *ph->shared->time_to_die)
	{
		ph->isdead = 1;
		return (1);
	}
	else if (*ph->shared->apetite == 0 ||
		ph->apetite == 0)
	{
		return (1);
	}
	else if (*ph->shared->apetite != -1 &&
		ph->apetite-- > 0 &&
		ph->shared->isdead == 0)
	{
		*ph->shared->apetite -= 1;
		pthread_mutex_lock(ph->lfork);
		pthread_mutex_lock(ph->rfork);
		gettimeofday(&ctv, NULL);
		ph_speak(ph_timest(1, (ctv.tv_sec * 1000) +
			(ctv.tv_usec / 1000)), ph->num, PHILO_EAT, ph->shared);
		usleep(*ph->shared->time_to_eat * 1000);
		ph->lastate = ph_timest(1, (ctv.tv_sec * 1000) +
			(ctv.tv_usec / 1000));
		pthread_mutex_unlock(ph->lfork);
		pthread_mutex_unlock(ph->rfork);
	}
	return (0);
}

short
	ph_sleep(t_philo *ph)
{
	struct timeval ctv;

	gettimeofday(&ctv, NULL);
	ph_speak(ph_timest(1, (ctv.tv_sec * 1000) +
		(ctv.tv_usec / 1000)), ph->num, PHILO_SLEEP, ph->shared);
	usleep(*ph->shared->time_to_sleep * 1000);
	return (0);
}

short
	ph_think(t_philo *ph)
{
	struct timeval ctv;

	gettimeofday(&ctv, NULL);
	ph_speak(ph_timest(1, (ctv.tv_sec * 1000) +
				(ctv.tv_usec / 1000)), ph->num, PHILO_THINK, ph->shared);
	return (0);
}
