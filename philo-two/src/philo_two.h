#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

typedef struct		s_shared
{
	unsigned int	*time_to_die;
	unsigned int	*time_to_eat;
	unsigned int	*time_to_sleep;
	sem_t			**forks;
	int				*max_ph;
	int				*time;
	bool			isdead;
	bool			allfull;
}					t_shared;

typedef struct		s_philo
{
	t_shared		*shared;
	bool			isdead;
	bool			isfull;
	long			lastate;
	long			time;
	int				num;
}					t_philo;

#endif
