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
	int	fpid;
	int	w;
	int	wstatus[1];

	if (argc  >= 2)
	{
		my_printf("Program name: %s\n", argv[1]);
		my_printf("Nb args: %d\n", argc - 2);
		my_printf("PID: %d\n", my_getpid());
		fpid = my_fork();
		if (fpid == 0)
		{
			my_printf("Child PID: %d\n", my_getpid());
			my_execve(argv[1], argv + 1, envp);
		}
		else
		{
			w = my_wait4(0, wstatus);
			if (wstatus[0] == 139)
			{
				my_printf("Segmentation fault (core dumped)\n");
				my_printf("Program terminated.\n");
				my_printf("Status: Segmentation fault\n");
			}
			else
			{
				my_printf("Program terminated.\n");
				my_printf("Status: OK\n");
			}
		}
	}

//	char	*input_command[1];
//	my_size_t	n[1];
//	char	*exec_arg[2];
//	int	i;
//
//	while (1)
//	{
//		*input_command = (char *)my_malloc(BUFFER_LEN * sizeof(char));
//		n[0] = BUFFER_LEN;
//		my_puts("M@ster, give me your input >");
//		my_getline(input_command, n, 0);
//		i = 0;
//		remove_newline(*input_command);
//		while (input_command[0][i] == ' ' && input_command[0][i] != '\0')
//			i++;
//		if (my_strncmp(input_command[0] + i, "exit", 4) == 0)
//		{
//			my_free(*input_command);
//			my_exit(0);
//		}
//		else if (my_strncmp(input_command[0] + i, "echo ", 5) == 0)
//		{
//			i = i + 4;
//			while (input_command[0][i] == ' ')
//				i++;
//			my_puts(input_command[0] + i);
//			my_puts("\n");
//			my_free(*input_command);
//		}
//		else if (my_strncmp(input_command[0] + i, "exec", 5) == 0)
//                {
//                        i = i + 4;
//                        while (input_command[0][i] == ' ')
//                                i++;
//			exec_arg[0] = "ls";
//			exec_arg[1] = (void *)0;
//                        my_execve("/bin/ls",exec_arg,envp);
//			my_puts("\n");
//                        my_free(*input_command);
//                }
//		else
//		{
//			my_puts("unknown command\n");
//			my_free(*input_command);
//		}
//	}
	return (0);
}
