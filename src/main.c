#include "../include/libc/libc.h"

#include <stdlib.h>
int	main(int argc, char **argv, char **envp)
{

	my_size_t	n[1];
	char	*buffer;
	buffer = (char *)malloc(16 * sizeof(char));


	*n = 0;

	my_puts("Write now : ");
	my_getline(&buffer, n, 0);

	my_puts("The buffer contains : ");
	my_puts(buffer);
	my_puts("\nAnd the allocated size is : ");
	my_putnbr(*n);

	return (0);
}
