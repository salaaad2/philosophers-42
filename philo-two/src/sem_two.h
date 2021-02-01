#ifndef SEM_TWO_H
#define SEM_TWO_H

#include <semaphore.h>
#include <fcntl.h>

sem_t	*ph_open_sem(char c, int status);

#endif // SEM_TWO_H
