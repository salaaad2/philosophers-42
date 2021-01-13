#ifndef PHILO_ONE_H
# define PHILO_ONE_H

typedef struct	s_philo {
    int num;
    int max_ph;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int appetite;
    int place;
    int hasfork;
    int isthinking;
    int iseating;
}				t_philo;

#endif
