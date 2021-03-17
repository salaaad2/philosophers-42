/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoenne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:53:32 by fmoenne-          #+#    #+#             */
/*   Updated: 2021/03/02 14:53:47 by fmoenne-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PHILO_EAT " is eating\n"
# define PHILO_FULL " All philosophers are full\n"
# define PHILO_FORKT " has taken a fork\n"
# define PHILO_FORKP " has put down a fork\n"
# define PHILO_SLEEP " is sleeping\n"
# define PHILO_THINK " is thinking\n"
# define PHILO_DEATH " died\n"

# include <pthread.h>
# include <stdbool.h>

typedef struct s_shared
{
	pthread_mutex_t	**forks;
	pthread_mutex_t	speaks;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				max_ph;
	int				apetite;
	long			time;
	bool			isdead;
	bool			allfull;
}					t_shared;

typedef struct s_philo
{
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	t_shared		*shared;
	long			ttd;
	bool			isdead;
	bool			isfull;
	long			lastate;
	long			time;
	int				apetite;
	int				num;
}					t_philo;

#endif
