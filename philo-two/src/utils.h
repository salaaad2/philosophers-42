/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoenne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:54:58 by fmoenne-          #+#    #+#             */
/*   Updated: 2021/03/02 14:54:59 by fmoenne-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWO_UTILS_H
# define TWO_UTILS_H

# include "philo_two.h"

int	ph_sem_init(t_shared *sh, int number);
void	ft_putstr(char *str);
short	ph_isfullnum(char *str);
int		ph_atoi(char *str);
short	ph_fills(int ac, char *av[], t_shared *sh);
long	ph_timest(short status, long ct);
short	ph_free(t_shared *sh, t_philo **pht);

#endif
