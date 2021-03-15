/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoenne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:53:29 by fmoenne-          #+#    #+#             */
/*   Updated: 2021/03/02 14:53:48 by fmoenne-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "philo.h"
# include <stdio.h>
# include <fcntl.h>

short		ph_speak(long ts, int nb, char *message, t_shared *sh);
long		ph_timest(void);
long		ph_cmptime(long time);
t_philo		ph_set(int i, t_shared *sh, t_philo ph);
short		ph_sem_init(t_shared *sh, int number);

#endif
