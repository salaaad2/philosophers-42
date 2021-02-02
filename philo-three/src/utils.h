#ifndef ONE_UTILS_H
# define ONE_UTILS_H

# include "philo_three.h"

int	ph_sem_init(t_shared *sh, int number);
void	ft_putstr(char *str);
short	ph_isfullnum(char *str);
int		ph_atoi(char *str);
short	ph_fills(int ac, char *av[], t_shared *sh);
long	ph_timest(short status, long ct);
short	ph_free(t_shared *sh, t_philo **pht);

#endif
