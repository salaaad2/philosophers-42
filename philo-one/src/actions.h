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

#ifndef ONE_ACTIONS_H
# define ONE_ACTIONS_H

# include "philo_one.h"

short ph_speak(long ts, int nb, char *message, t_shared *sh);
short ph_eat(t_philo *ph);

#endif
