#include "sem_two.h"

sem_t *
ph_open_sem(char c, int status)
{
    sem_unlink((char*)&c);
    return (sem_open((char*)&c, O_CREAT | O_EXCL, 0644, status));
}
