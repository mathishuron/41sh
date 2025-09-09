#include "../include/libc/libc.h"

void	init_base(void)
{
	//create file and set an entry as master password
	return;
}

int	check_password(char *file)
{

}

void	add_entry(void)
{
	return;
}

char	*get_base(char *file)
{
	int	fd;
	int	bytes_read;
	char	*buffer[1];
	my_size_t	buffer_size[1];

	buffer[0] = (char *)my_malloc(BUFFER_LEN * sizeof(char));
	buffer_size[0] = BUFFER_LEN;
	fd = my_open(file, O_RDONLY | O_CREAT);
	if (fd == -1)
	{
		my_printf("Error opening file\n");
		my_exit(1);
	}
	bytes_read = my_getfile(buffer, buffer_size, fd);
	my_close(fd);
	return (buffer[0]);

}

char	*retrieve_password(char *file, char *entry)
{
	int	fd;
	int	i;
	int	j;
	int	size_password;
	int	len_entry;
	char	*buffer[1];
	char	*password;
	
	buffer[0] = get_base(file);

	i = 0;
	while (buffer[0][i] != '\0')
	{
		len_entry = my_strlen(entry);
		if (my_strncmp(entry, buffer[0] + i, len_entry) == 0 && buffer[0][i + len_entry] == ' ')
		{
			i += len_entry;
			i++;
			while (buffer[0][i + size_password] != '\n')
				size_password++;
			password = (char *)my_malloc((size_password + 1) * sizeof(char));
			j = 0;
			while (j < size_password)
			{
				password[j] = buffer[0][i + j];
				j++;
			}
			password[j] = '\0';
			return (password);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd;
	int	bytes_read;
	char	*buffer[1];
	my_size_t	buffer_size[1];
	
	if (argc >= 2)
	{
		if (my_strcmp(argv[1], "get") == 0)
		{
			if (argc < 4)
				my_printf("Not enough argument for get\n");
			else if (retrieve_password(argv[2], argv[3]) == 0)
				my_printf("Entry not found\n");
			else
				my_printf(retrieve_password(argv[2], argv[3]));
		}
		else if (my_strcmp(argv[1], "list") == 0)
		{
			if (argc < 3)
				my_printf("Missing DB name for list");
			else
				my_printf(get_base(argv[2]));
		}

	}
	else
	{
		my_printf("Not enough arguments\n");
	}
	my_free();
	return (0);

}
