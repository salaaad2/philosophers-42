#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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
