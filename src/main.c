#include "../include/libc/libc.h"

void	remove_newline(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			break;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input_command[1];
	my_size_t	n[1];
	int	i;

	while (1)
	{
		*input_command = (char *)my_malloc(BUFFER_LEN * sizeof(char));
		n[0] = BUFFER_LEN;
		my_puts("M@ster, give me your input >");
		my_getline(input_command, n, 0);
		i = 0;
		remove_newline(*input_command);
		while (input_command[0][i] == ' ' && input_command[0][i] != '\0')
			i++;
		if (my_strncmp(input_command[0] + i, "exit", 4) == 0)
		{
			my_free(*input_command);
			my_exit(0);
		}
		else if (my_strncmp(input_command[0] + i, "echo ", 5) == 0)
		{
			i = i + 4;
			while (input_command[0][i] == ' ')
				i++;
			my_puts(input_command[0] + i);
			my_puts("\n");
			my_free(*input_command);
		}
		else
		{
			my_puts("unknown command\n");
			my_free(*input_command);
		}
	}
	return (0);
}
