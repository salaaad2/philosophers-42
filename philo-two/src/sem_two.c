#include "sem_two.h"

int
ph_open_sem(t_shared *sh, int max_ph)
{
    if ((sh->forks = sem_open("/forks", O_CREAT, 0777, max_ph)) == SEM_FAILED
        || sem_unlink("/forks"))
        return (1);
    return (1);
}
