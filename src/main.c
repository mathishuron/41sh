#include "../include/libc/libc.h"

char	*ROT13(char *str)
{
	int	i;
	char	*rot;

	i = 0;

	rot = (char *)my_malloc(my_strlen(str + 1) * sizeof(char));
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			rot[i] = (((str[i] - 'a') + 13 ) % 26) + 'a';
		else if (str[i] >= 'A' && str[i] <= 'Z')
			rot[i] = (((str[i] - 'A') + 13 ) % 26) + 'A';
		else
			rot[i] = str[i];
		i++;
	}
	rot[my_strlen(str)] = '\0';
	return (rot);
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
	return (ROT13(buffer[0]));

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
	size_password = 0;
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

void	add_entry(char *file, char *entry)
{
	int	fd;
	int	i;
	int	bytes_read;
	char	*buffer[1];
	my_size_t	buffer_size[1];
	
	i = 0;
	if (retrieve_password(file, entry) == 0)
	{
		fd = my_open(file, O_APPEND| O_WRONLY);
		if (fd == -1)
		{
			my_printf("Error opening file\n");
			my_exit(1);
		}
		my_write(fd, ROT13(entry), my_strlen(entry));
		my_write(fd, " ", 1);
		buffer[0] = (char *)my_malloc(BUFFER_LEN * sizeof(char));
		buffer_size[0] = BUFFER_LEN;
		my_printf("Enter password for entry %s : ", entry);
		bytes_read = my_getline(buffer, buffer_size, 0);
		while (i < bytes_read)
		{
			if (buffer[0][i] == ' ')
			{
				my_printf("Password cannot contain space\n");
				my_close(fd);
				my_free();
				my_exit(1);
			}
			i++;
		}
		my_write(fd, ROT13(buffer[0]), bytes_read);
		my_printf("Saved successfully.\n");
		my_close(fd);
	}
	else
		my_printf("Error : entry already exists\n");

	return;
}

void	init_base(char *file)
{
	if (retrieve_password(file, "master-password") == 0)
		add_entry(file, "master-password");
	else
		my_printf("Database already exists\n");
	return;
}

void	check_password(char *file, char **password, my_size_t *password_size)
{
	char	*db_pass;

	my_printf("Enter master password : ");
	my_getline(password, password_size, 0);
	db_pass = retrieve_password(file, "master-password");
	if (db_pass != 0 && my_strncmp(db_pass, password[0], my_strlen(db_pass)) == 0)
		return;
	else
	{
		my_printf("Wrong password\n");
		my_free();
		my_exit(1);
	}
}

void	generate(void)
{
	int	fd;
	int	i;
	char	buffer[1];
	char	password[11];

	password[10] = '\0';
	i = 0;
	fd = my_open("/dev/random",O_RDONLY);
	if (fd < 0)
	{
		my_printf("Error accessing random generator on system\n");
		my_exit(1);
	}
	while (i < 10)
	{
		my_read(fd, buffer, 1);
		if ((buffer[0] >= 'a' && buffer[0] <= 'z') || (buffer[0] >= '0' && buffer[0] <= '9'))
		{
			password[i] = buffer[0];
			i++;
		}
	}
	my_printf("Your randomly generated password : %s\n", password);
}



int	main(int argc, char **argv, char **envp)
{
	char	*password[1];
	my_size_t	password_size[1];
	
	password[0] = (char *)my_malloc(BUFFER_LEN * sizeof(char));
	password_size[0] = BUFFER_LEN;

	if (argc >= 2)
	{
		if (my_strcmp(argv[1], "get") == 0)
		{
			if (argc < 4)
				my_printf("Bad usage, use \"get <vault_name> <site>\"\n");
			else
			{
				check_password(argv[2], password, password_size);
				if (retrieve_password(argv[2], argv[3]) == 0)
					my_printf("Entry not found\n");
				else
					my_printf(retrieve_password(argv[2], argv[3]));
			}
		}
		else if (my_strcmp(argv[1], "list") == 0)
		{
			if (argc < 3)
				my_printf("Bad usage, use \"list <vault_name>\"\n");
			else
			{
				check_password(argv[2], password, password_size);
				my_printf(get_base(argv[2]));
			}
		}
		else if (my_strcmp(argv[1], "add") == 0)
		{
			if (argc < 4)
				my_printf("Bad usage, use \"add <vault_name> <site>\"\n");
			else
			{
				check_password(argv[2], password, password_size);
				add_entry(argv[2], argv[3]);
			}
		}
		else if (my_strcmp(argv[1], "init") == 0)
		{
			if (argc < 3)
				my_printf("Bad usage, use \"init <vault_name>\"\n");
			else
				init_base(argv[2]);
		}
		else if (my_strcmp(argv[1], "generate") == 0)
			generate();

		else
		{
			my_printf("Unknown command : %s\n", argv[1]);
			my_printf("Commands: init, add, list, get, generate\n");
		}
	}
	else
	{
		my_printf("Usage: %s <command> [args...]\n", argv[0]);
		my_printf("Commands: init, add, list, get, generate\n");
	}
	my_free();
	return (0);
}
