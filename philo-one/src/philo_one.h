#ifndef PHILO_ONE_H
# define PHILO_ONE_H

typedef struct	s_shared {
	int		*max_ph;
	int		*time_to_die;
	int		*time_to_eat;
	int		*time_to_sleep;
	int		*appetite;
	int		*time;
} t_shared;

typedef struct	s_philo {
	t_shared *shared;
	long	time;
	int		num;
	int		place;
	int		hasfork;
	int		isthinking;
	int		iseating;
}				t_philo;

#endif
