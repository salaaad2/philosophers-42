#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <pthread.h>

typedef struct		s_shared {
	pthread_mutex_t pmt;
	unsigned int	*time_to_die;
	unsigned int	*time_to_eat;
	unsigned int	*time_to_sleep;
	int				*max_ph;
	int				*appetite;
	int				*time;
}					t_shared;

typedef struct	s_philo {
	t_shared *shared;
	long	time;
	int		num;
	int		hasfork;
	int		isthinking;
	int		iseating;
	int		issleeping;
}				t_philo;

#endif
