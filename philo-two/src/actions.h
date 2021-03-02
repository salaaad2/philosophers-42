/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoenne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:54:47 by fmoenne-          #+#    #+#             */
/*   Updated: 2021/03/02 14:54:47 by fmoenne-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWO_ACTIONS_H
# define TWO_ACTIONS_H

# include "philo_two.h"

short ph_speak(long ts, int nb, char *message, t_shared *sh);
short ph_eat(t_philo *ph);

#endif
