#include "../include/libc/libc.h"

#define BUFFER_LEN 3

my_ssize_t my_write(int fd, const void *str, my_size_t len)
{
	long ret;
	__asm__ volatile (
        "mov $1, %%rax\n"   // syscall: write hello
        "mov %1, %%rdi\n"   // fd
        "mov %2, %%rsi\n"   // str
        "mov %3, %%rdx\n"   // len
        "syscall\n"
        : "=a"(ret)
        : "r"((long)fd), "r"(str), "r"(len)
        : "rdi", "rsi", "rdx"
    );
    return ret;
}

int	my_putchar(int c)
{
	my_write(1, &c, 1);
	return (1);
}

int	my_puts(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		my_putchar(str[i]);
		i++;
	}
	// my_putchar('\n'); Removed for printf exercice
	return (i);
}

void	recurse_display_putnbr(int n, int *counter)
{
	if (n <= -10)
		recurse_display_putnbr(n / 10, counter);
	my_putchar('0' - n % 10);
	*counter = *counter + 1;
}

int	my_putnbr(int n)
{
	int	i;

	i = 0;
	if (n >= 0)
		n *= -1;
	else
	{
		i += my_putchar('-');
	}
	recurse_display_putnbr(n, &i);
	return (i);
}

int	my_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	my_strncmp(const char *s1, const char *s2, my_size_t n)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && i < n)
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

my_ssize_t	my_read(int fd, void *buf, my_size_t len)
{
	long ret;
	__asm__ volatile (
        "mov $0, %%rax\n"   // syscall: read
        "mov %1, %%rdi\n"   // fd
        "mov %2, %%rsi\n"   // buf
        "mov %3, %%rdx\n"   // len
        "syscall\n"
        : "=a"(ret)
        : "r"((long)fd), "r"(buf), "r"(len)
        : "rdi", "rsi", "rdx"
    );
    return ret;
}

int	my_pos(char c, char *buffer, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (buffer[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void my_strncpy(char *src, char *dst, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

//my_ssize_t	my_getline(char **lineptr, my_size_t *n, int fd)
//{
//	my_ssize_t	i;
//	my_ssize_t	count;
//	int		pos;
//	char		*temp_dest;
//
//	count = 0;
//	i = my_read(fd, *lineptr + count, BUFFER_LEN);
//	count += i;
//
//	while (i != 0)
//	{
//		pos = my_pos('\n', *lineptr, count); 
//		if (pos >= 0)
//		{
//			if (pos == *n - 1) //manage newline at last position
//			{
//				temp_dest = (char *)malloc((*n + 1) * sizeof(char)); //replace with custom alloc
//				my_strncpy(*lineptr,temp_dest, *n);
//				*n += 1;
//				free(*lineptr); // replace
//				*lineptr = temp_dest;
//
//			}
//			lineptr[0][pos + 1] = '\0';
//			break;
//		}
//		else if (my_pos('\0', *lineptr, count) >= 0)
//			break;
//		else if (count < *n)
//			break;
//		else
//		{
//			temp_dest = (char *)malloc((*n + BUFFER_LEN) * sizeof(char)); //replace
//			my_strncpy(*lineptr,temp_dest, *n);
//			*n += BUFFER_LEN;
//			free(*lineptr); //replace
//			*lineptr = temp_dest;
//			i = my_read(fd, *lineptr + count, BUFFER_LEN);
//			count += i;
//		}
//	}
//	if (count < *n) //EOF
//		lineptr[0][count] = '\0';
//	return (count);
//}

[[noreturn]] void exit(int status)
{
	__asm__ volatile(
			"syscall"
			:
			: "a"(60),
			"D" (status)
			: "rcx", "r11", "memory");
	__builtin_unreachable();
}

int my_printf(const char *format, ...)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == 's')
			{
				count += my_puts("Bondour");
				i = i + 2;
			}
			else if (format[i + 1] == 'd')
			{
				count += my_putnbr(44444);
				i = i + 2;
			}
			else if (format[i + 1] == 'c')
			{
				count += my_putchar('X');
				i = i + 2;
			}
			else
			{
				my_putchar('%');
				count++;
				i++;
			}
		}
		else
		{
			my_putchar(format[i]);
			count++;
			i++;
		}
	}
	return (count);
}
