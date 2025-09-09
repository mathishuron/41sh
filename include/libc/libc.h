#ifndef LIBC_H
# define LIBC_H

#include <unistd.h>

#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02
#define O_CREAT 0100
#define BUFFER_LEN 16

typedef unsigned long long	my_size_t;
typedef long long	my_ssize_t;

my_ssize_t	my_write(int fd, const void *str, my_size_t len);
int	my_putchar(int c);
int	my_puts(const char *str);
int	my_putnbr(int n);
int	my_strlen(char *str);
int	my_strcmp(const char *s1, const char *s2);
int	my_strncmp(const char *s1, const char *s2, my_size_t n);
my_ssize_t	my_read(int fd, void *buf, my_size_t len);
my_ssize_t	my_getfile(char **lineptr, my_size_t *n, int fd);
my_ssize_t	my_getline(char **lineptr, my_size_t *n, int fd);
[[noreturn]] void	my_exit(int status);
int	my_printf(const char *format, ...);
void	*my_sbrk(int increment);
void	*my_malloc(my_size_t size);
void	my_free(void);
void	*my_realloc(void *ptr, size_t size);
int	my_execve(const char *pathname, char *const argv[], char *const envp[]);
int	my_fork(void);
int	my_getpid(void);
int	my_wait4(int pid, int *wstatus);
int	my_pipe(int *fildes);
int	my_dup2(int oldfd, int newfd);
void	my_close(int fd);
int	my_open(const char *path, int flags);

#endif
