#include "../include/libc/libc.h"

int	main(int argc, char **argv, char **envp)
{
	int	a;
	
	a = my_printf("AAAAA%");
	my_putnbr(a);
	return (0);
}
