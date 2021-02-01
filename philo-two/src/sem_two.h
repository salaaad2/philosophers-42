#ifndef SEM_TWO_H
#define SEM_TWO_H

#include <semaphore.h>
#include <fcntl.h>

#include "philo_two.h"

int ph_open_sem(t_shared *ph, int max_ph);

#endif
