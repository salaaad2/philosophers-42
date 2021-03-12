

void
ph_putchar(char c)
{
	write(1, &c, 1);
}

void
ph_putnbr(long nbr)
{
	if (nbr >= 10)
	{
		ph_putnbr(nbr / 10);
		ph_putnbr(nbr % 10);
	}
	else
		ph_putchar(nbr + 48);
}

void
ph_putstr(char *str)
{
	int i = -1;

	while (str[++i])
		ph_putchar(str[i]);
}

void		printstatus(long ts, long nb, char *message)
{
	ph_putnbr(ts);
	ph_putnbr(nb);
	ph_putstr(message);
}
