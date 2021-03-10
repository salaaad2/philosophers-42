/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoenne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:54:53 by fmoenne-          #+#    #+#             */
/*   Updated: 2021/03/02 14:54:53 by fmoenne-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# define PHILO_EAT "is eating"
# define PHILO_FULL "All philosophers are full"
# define PHILO_FORKT "has taken a fork"
# define PHILO_FORKP "has put down a fork"
# define PHILO_SLEEP "is sleeping"
# define PHILO_THINK "is thinking"
# define PHILO_DEATH "died"
# define PHILO_SEMF "/forks"
# define PHILO_SEMS "/speaks"

# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>

typedef struct		s_shared
{
	pid_t			pid;
	sem_t			*forks;
	sem_t			*speaks;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				max_ph;
	int				apetite;
	int				time;
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
	int				apetite;
	int				num;
}					t_philo;

#endif
