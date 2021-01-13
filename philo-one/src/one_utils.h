#ifndef ONE_UTILS_H
#define ONE_UTILS_H

#include "philo_one.h"

void	ft_putstr(char *str);
short	ph_isfullnum(char *str);
int	ph_atoi(char *str);
void	ph_fills(int ac, char *av[], t_philo *ph);
long	ph_timest(short status, long ct);

#endif
