#ifndef LIBC_H
# define LIBC_H

typedef unsigned long long my_size_t;
typedef long long my_ssize_t;

my_ssize_t my_write(int fd, const void *str, my_size_t len);
int my_putchar(int c);
int my_puts(const char *str);
void my_putnbr(int n);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, my_size_t n);
my_ssize_t my_read(int fd, void *buf, my_size_t len);
my_ssize_t      my_getline(char **lineptr, my_size_t *n, int fd);
[[noreturn]] void exit(int status);

#endif
