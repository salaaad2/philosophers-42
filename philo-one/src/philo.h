#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# define PHILO_EAT "is eating"
# define PHILO_FULL "All philosophers are full"
# define PHILO_FORKT "has taken a fork"
# define PHILO_FORKP "has put down a fork"
# define PHILO_SLEEP "is sleeping"
# define PHILO_THINK "is thinking"
# define PHILO_DEATH "died"

# include <pthread.h>
# include <stdbool.h>

typedef struct		s_shared
{
	pthread_mutex_t	**forks;
	pthread_mutex_t	speaks;
	unsigned int	*time_to_die;
	unsigned int	*time_to_eat;
	unsigned int	*time_to_sleep;
	int				*max_ph;
	int				*apetite;
	int				*time;
	bool			isdead;
	bool			allfull;
}					t_shared;

typedef struct		s_philo
{
	pthread_mutex_t *lfork;
	pthread_mutex_t *rfork;
	t_shared		*shared;
	bool			isdead;
	bool			isfull;
	long			lastate;
	long			time;
	int				apetite;
	int				num;
}					t_philo;

#endif
