/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoenne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:54:14 by fmoenne-          #+#    #+#             */
/*   Updated: 2021/03/02 14:54:14 by fmoenne-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "utils.h"
#include "actions.h"
#include "philo_three.h"

short
	ph_speak(long ts, int nb, char *message, t_shared *sh)
{
	sem_wait(sh->speaks);
	printf("[%ld]%d %s\n", ts, nb, message);
	sem_post(sh->speaks);
	return (1);
}
