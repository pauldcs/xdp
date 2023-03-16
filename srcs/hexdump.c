#include "hexdump.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>

static char    *__screen__;
static int     __screen_offset__ = 0;

static size_t	write_all(int fd, const void *buf, size_t s)
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

static inline void	write_pointer(const uintptr_t p, size_t width)
{
	char		*buffer = (__screen__ + __screen_offset__);
	uintptr_t	ptr;
	int			i;

	i = width;
	ptr = (uintptr_t)p;
	do {
		buffer[--i] = BASE[ptr & 0xf];
		ptr >>= 4;
	} while (ptr && i);
	while (i)
		buffer[--i] = '0';
	__screen_offset__ += width;
}

static inline void	write_16_bytes_spaced(const void *addr, size_t size)
{
	char	*buffer = (__screen__ + __screen_offset__);
	char	*ptr;
	size_t  i;

	i = 0;
	ptr = (char *)addr;
	while (size-- && i < 48) {
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
	while (i < 48)
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
		*tmp >= 36 && *tmp < 127 ?
			(buffer[i++] = *tmp) : (buffer[i++] = '.');
		tmp++;
	}
	__screen_offset__ += i;
}

bool raw_bytes_dump(const void *addr, size_t size)
{
	char	*ptr = (char *)addr;

	if ((__screen__ = malloc(size * 2 + 1)) == NULL)
		return (false);
	while (size--)
	{
		if (*ptr) {
			*(__screen__ + (__screen_offset__++)) = BASE[(*ptr >> 4) & 0xf];
			*(__screen__ + (__screen_offset__++)) = BASE[*ptr & 0xf];
		} else {
			*(int16_t*)(__screen__ + (__screen_offset__)) = 0x2e2e;
			__screen_offset__ += 2;
		}
		ptr++;
	}
	*(__screen__ + (__screen_offset__++)) = '\n';
	print_screen();
	free(__screen__);
	return (true);
}

bool	classic_hexdump_c(const void *addr, size_t n)
{
	size_t		size;
	const void 	*tmp = addr;

	if ((__screen__ = malloc(79 << 5)) == NULL)
		return (false);
	while (n) {
		size = (n > 16 ? 16 : n);
		if (tmp != addr && !memcmp(addr - 16, addr, 16)) {
			if (__screen_offset__) {
				print_screen();
				write(1, "<snip>\n", 7);
			}
		} else {
			write_pointer((uintptr_t)(addr - tmp), 10);
			screen_write_string(":  ");
			write_16_bytes_spaced(addr, size);
			screen_write_string(" ");
			write_16_ascii(addr, size);
			screen_write_string("\n");
        	if (__screen_offset__ >= 79 << 5)
				print_screen();
		}
        addr += size;
		n -= size;
	}
    if (__screen_offset__)
		print_screen();
	free(__screen__);
	return(true);
}

int hexdump(const char *filename, t_mode mode)
{
	void 		*map;
	int 		fd;
	struct stat	st;

	if (stat(filename, &st) == -1
		|| (fd = open(filename, O_RDONLY)) == -1)
		return (perror(0), EXIT_FAILURE);
	map = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (map == MAP_FAILED)
		return (EXIT_FAILURE);
	switch (mode) {
		case CLASSIC:
			classic_hexdump_c(map, st.st_size);
			break;
		case DUMP_RAW:
			raw_bytes_dump(map, st.st_size);
			break;
		default: break;
	}
	write(1, "\n", 1);
	return (
		munmap(map, st.st_size),
		EXIT_SUCCESS);
}
