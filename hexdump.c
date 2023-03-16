#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SCREEN_LINE_SIZE 79
#define BASE "0123456789abcdef"

static char 	*__screen__;
static int 		__screen_offset__ = 0;

size_t	write_all(int fd, const void *buf, size_t s)
{
	ssize_t	c;
	size_t	ret;

	ret = 0;
	while (s)
	{
		c = write(fd, buf + ret, s);
		if (c == -1)
			continue ;
		ret += c;
		s -= c;
	}
	return (ret);
}

static void print_screen(void)
{
	write_all(STDOUT_FILENO,
		__screen__,
		__screen_offset__);
	__screen_offset__ = 0;
}

static void screen_write_string(const char *str)
{
	while (*str) {
		*(__screen__ + (__screen_offset__)) = *str++;
		__screen_offset__++;
	}
}

static inline void	write_offset(const uintptr_t p)
{
	char		*buffer = (__screen__ + __screen_offset__);
	uintptr_t	ptr;
	int			i;

	i = 10;
	ptr = (uintptr_t)p;
	do {
		buffer[--i] = BASE[ptr & 0xf];
		ptr >>= 4;
	} while (ptr && i);
	while (i)
		buffer[i--] = '0';
	__screen_offset__ += 10;
}

static inline void	write_16_bytes_spaced(const void *addr, size_t size)
{
	char	*buffer = (__screen__ + __screen_offset__);
	char	*ptr;
	size_t  i;

	i = 0;
	ptr = (char *)addr;
	while (size-- && i < 47) {
		if (*ptr) {
			buffer[i++] = BASE[(*ptr >> 4) & 0xf];
			buffer[i++] = BASE[*ptr & 0xf];
		} else {
			*(int16_t*)(buffer + i) = 0x2e2e;
			i += 2;
		}
		buffer[i++] = ' ';
		ptr++;
	}
	while (i < 47)
		buffer[i++] = ' ';
	__screen_offset__ += i;
}

static inline void	write_16_ascii(const void *s, size_t size)
{
	char	*buffer = (__screen__ + __screen_offset__);
	int8_t 	*tmp;
	size_t	i;

	i = 0;
	tmp = (int8_t *)s;
	while (size-- && i < 16) {
		*tmp>=36&&*tmp<127 ?
			(buffer[i++] = *tmp) : (buffer[i++] = '.');
		tmp++;
	}
	__screen_offset__ += i;
}

static void	classic_hexdump_c(const void *addr, size_t n)
{
	size_t		size;
	const void 	*tmp = addr;

	while (n) {
		size = (n > 16 ? 16 : n);
		if (tmp != addr && !memcmp(addr - 16, addr, 16)) {
			if (__screen_offset__) {
				print_screen();
				write (STDOUT_FILENO, "<snip>\n", 7);
			}
		} else {
			write_offset(addr - tmp);
			screen_write_string(":  ");
			write_16_bytes_spaced(addr, size);
			screen_write_string(" ");
			write_16_ascii(addr, size);
			screen_write_string("\n");
        	if (__screen_offset__ >= SCREEN_LINE_SIZE << 5)
				print_screen();
		}
        addr += size;
		n -= size;
	}
    if (__screen_offset__)
		print_screen();
}

int hexdump(const char *filename)
{
	void 		*map;
	int 		fd;
	struct stat	st;
	
	if ((__screen__ = malloc(SCREEN_LINE_SIZE << 5)) == NULL)
		return (EXIT_FAILURE);
	if (stat(filename, &st) == -1
		|| (fd = open(filename, O_RDONLY)) == -1)
		return (
			perror(0),
			free(__screen__),
			EXIT_FAILURE);
	map = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (map == MAP_FAILED)
		return (
			free(__screen__),
			EXIT_FAILURE);

	classic_hexdump_c(map, st.st_size);
	write(STDOUT_FILENO, "\n", 1);
	return (
		munmap(map, st.st_size),
		free(__screen__),
		EXIT_SUCCESS);
}

int main(int ac, char *av[])
{
	int ret;

	if (ac < 2) {
		write(STDERR_FILENO, "Error: Usage\n", 14);
		return (EXIT_FAILURE);
	}
	while (--ac)
		ret = hexdump(*++av);
	return (ret);
}