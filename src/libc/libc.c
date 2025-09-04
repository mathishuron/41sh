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

my_ssize_t	my_getline(char **lineptr, my_size_t *n, int fd)
{
	my_ssize_t	i;
	my_ssize_t	count;
	int		pos;
	char		*temp_dest;

	count = 0;
	i = my_read(fd, *lineptr + count, BUFFER_LEN);
	count += i;

	while (i != 0)
	{
		pos = my_pos('\n', *lineptr, count); 
		if (pos >= 0)
		{
			if (pos == *n - 1) //manage newline at last position
			{
				temp_dest = (char *)my_malloc((*n + 1) * sizeof(char));
				my_strncpy(*lineptr,temp_dest, *n);
				*n += 1;
				// don't forget to free(*lineptr);
				*lineptr = temp_dest;

			}
			lineptr[0][pos + 1] = '\0'; // not pos ? to check
			break;
		}
		else if (my_pos('\0', *lineptr, count) >= 0)
			break;
		else if (count < *n)
			break;
		else
		{
			temp_dest = (char *)my_malloc((*n + BUFFER_LEN) * sizeof(char));
			my_strncpy(*lineptr,temp_dest, *n);
			*n += BUFFER_LEN;
			// don't forget to free(*lineptr);
			*lineptr = temp_dest;
			i = my_read(fd, *lineptr + count, BUFFER_LEN);
			count += i;
		}
	}
	if (count < *n) //EOF
		lineptr[0][count] = '\0'; //check if not count - 1 actually ?
	return (count);
}

[[noreturn]] void my_exit(int status)
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
	__builtin_va_list args;

	count = 0;
	i = 0;
	__builtin_va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == 's')
			{
				count += my_puts(__builtin_va_arg(args, char *));
				i = i + 2;
			}
			else if (format[i + 1] == 'd')
			{
				count += my_putnbr(__builtin_va_arg(args, int));
				i = i + 2;
			}
			else if (format[i + 1] == 'c')
			{
				count += my_putchar(__builtin_va_arg(args, int));
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
	__builtin_va_end(args);
	return (count);
}

static void	*program_break = (void *)0;
static int	heap_size = 0;

void	*my_sbrk(int increment)
{
	void	*old_brk;

	if (program_break == 0)
	{
		__asm__ volatile (
				"mov $12, %%rax\n"
				"xor %%rdi, %%rdi\n"
				"syscall\n"
				: "=a"(program_break)
				:
				: "rdi"
				);
	}
	old_brk = program_break;
	program_break += increment;
	heap_size += increment;
	__asm__ volatile (
			"mov $12, %%rax\n"
			"syscall\n"
			:
			: "D"(program_break)
			:
			);
	return (old_brk);
}

void	*my_malloc(my_size_t size)
{
	size = size + (8 - (size % 8)); // memory alignment on 8 bytes
	return (my_sbrk(size));
}

void	my_free(void *ptr)
{
	(void)ptr;
	my_sbrk(-heap_size);
	heap_size = 0;
	program_break = 0;
}

void	*my_realloc(void *ptr, size_t size)
{
	void	*new_pointer;

	new_pointer = my_malloc(size);
	my_strncpy(ptr, new_pointer, size); // will copy more than the original
	return (new_pointer);
}
