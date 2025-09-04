#include "../include/libc/libc.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd;
	int	n[1];
	char 	*lineptr;
	
	lineptr = (char *)my_malloc(BUFFER_LEN * sizeof(char));
	*n = BUFFER_LEN;
	// to test getline

	if (argc < 2)
	{
		my_puts("Error: missing --user <username> argument\n");
		my_exit(1);
	}
	else if (my_strcmp(argv[1],"--user") != 0)
	{
		my_puts("Error: unrecognized argument '");
		my_puts(argv[1]);
		my_puts("'\n");
		my_exit(1);
	}
	else if (argc < 3)
	{
		my_puts("Error: missing value for --user\n");
		my_exit(1);
	}
	else
	{
		my_puts("Hello ");
		my_puts(argv[2]);
		my_puts("\n");
	}
	return (0);
}
