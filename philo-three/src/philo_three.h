#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>

typedef struct		s_shared
{
	sem_t			*forks;
	unsigned int	*time_to_die;
	unsigned int	*time_to_eat;
	unsigned int	*time_to_sleep;
	int				*max_ph;
	int				*appetite;
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
	int				ate;
}					t_philo;

#endif
