/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoenne- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:54:44 by fmoenne-          #+#    #+#             */
/*   Updated: 2021/03/02 14:54:45 by fmoenne-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "utils.h"
#include "actions.h"
#include "philo_two.h"

short
	ph_speak(long ts, int nb, char *message, t_shared *sh)
{
	sem_wait(sh->speaks);
	printf("[%ld]%d %s\n", ts, nb, message);
	sem_post(sh->speaks);
	return (1);
}
