/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoenne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:53:40 by fmoenne-          #+#    #+#             */
/*   Updated: 2021/03/02 14:53:59 by fmoenne-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ONE_UTILS_H
# define ONE_UTILS_H

# include "philo.h"

void	ft_putstr(char *str);
void	ph_exit(t_philo *pht);
short	ph_isfullnum(char *str);
int		ph_atoi(char *str);
short	ph_fills(int ac, char *av[], t_shared *sh);

#endif
