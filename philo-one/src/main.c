#include "one_utils.h"

int main(int ac, char *av[])
{
    if (ac <= 4 || ac >= 6)
    {
        ft_putstr("wrong number of arguments");
        ft_putstr(av[1]);
        return (1);
    }
    return 0;
}
