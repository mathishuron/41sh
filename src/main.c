#include "../include/libc/libc.h"

int	main(int argc, char **argv, char **envp)
{
	my_size_t	n[1];
	char 	*lineptr;
	my_ssize_t	char_read;
	
	lineptr = (char *)my_malloc(BUFFER_LEN * sizeof(char));
	*n = BUFFER_LEN;
	my_printf("Write there : >");
	char_read = my_getline(&lineptr, n, 0);
	my_printf("\nBuffer filled with : %s", lineptr);
	my_printf("\nBuffer total size : %d", n[1]);
	my_printf("\nCharacter written : %d", char_read);
	my_free(lineptr);
	my_printf("\nHook here for no heap");

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
