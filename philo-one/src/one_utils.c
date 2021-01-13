#include "one_utils.h"

#include <unistd.h>
#include <stdio.h>

int
	ph_atoi(char *str)
{
    int n;

    n = 0;
    if (*str == 0)
        return (0);
    while (*str)
        n = n * 10 + (*str++ - 48);
    return (n);
}

void
	ft_putstr(char *str)
{
    int i;

    i = -1;
    while (str[i])
    {
        write(1, &str[++i], 1);
    }
}

short ph_isfullnum(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (!(str[i] > 47 && str[i] < 58))
            return (0);
    }
    return (1);
}
