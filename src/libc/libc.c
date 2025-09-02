#include "../include/libc/libc.h"

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
	return (c);
}

int	my_puts(const char *str)
{
	int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		my_putchar(*(str + i));
		i++;
	}
	my_putchar('\n');
	return (0);
}

void	recurse_display_putnbr(int n)
{
	if (n <= -10)
		recurse_display_putnbr(n / 10);
	my_putchar('0' - n % 10);
}

void	my_putnbr(int n)
{
	if (n >= 0)
		n *= -1;
	else
		my_putchar('-');
	recurse_display_putnbr(n);
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

my_ssize_t	my_getline(char **lineptr, my_size_t *n, int fd)
{
	my_ssize_t i;

	i = 0;
	while (read(fd, *lineptr + i, 1) != 0 && i < *n - 1)
	{
		if (lineptr[0][i] == '\n')
		{
			i++;
			break;
		}
		i++;
	}
	*lineptr[i] = '\0';
	return (i);
}
