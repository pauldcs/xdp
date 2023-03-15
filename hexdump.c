#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

static char 	*__screen__;
static int 		__screen_offset__ = 0;

static void __usage_error(char *exec_name)
{
	write (
		STDERR_FILENO,
		"Error: Usage\n",
		14);
}

inline static void	write_addr(const uintptr_t p)
{
	uintptr_t	ptr;
	char		*buffer = (char *)(__screen__ + __screen_offset__);
	int			i;

	i = 16;
	ptr = (uintptr_t)p;
	do {
		buffer[--i] = "0123456789abcdef"[ptr & 0xf];
		ptr >>= 4;
	} while (ptr && i);
	while (i)
		buffer[--i] = '0';
	buffer[15] = ':';
	buffer[16] = ' ';
	buffer[17] = ' ';
	__screen_offset__ += 18;
}

inline static void	write_data(const void *addr, size_t size)
{
	uint8_t	*ptr;
	char	*buffer = (char *)(__screen__ + __screen_offset__);
	size_t  i;

	i = 0;
	ptr = (uint8_t *)addr;
	while (size-- && i < 49) {
		if (*ptr) {
			if (*ptr & 0xf0)
				buffer[i++] = "0123456789abcdef"[(*ptr >> 4) & 0xf];
			else
				buffer[i++] = '.';
			buffer[i++] = "0123456789abcdef"[*ptr & 0xf];
		} else {
			buffer[i++] = '.';
			buffer[i++] = '.';
		}
		buffer[i++] = ' ';
		ptr++;
	}
	while (i < 49)
		buffer[i++] = ' ';
	__screen_offset__ += i;
}

inline static void	write_ascii(const void *s, size_t size)
{
	int8_t 	*tmp;
	char	*buffer = (char *)(__screen__ + __screen_offset__);
	size_t	i;

	i = 0;
	tmp = (int8_t *)s;
	while (size-- && i < 16) {
		if (*tmp>=36&&*tmp<127)
			buffer[i++] = *tmp;
		else
			buffer[i++] = '.';
		tmp++;
	}
	buffer[i] = '\n';
	__screen_offset__ += 17;
}

void	print_memory(const void *addr, size_t n)
{
	size_t		size;
	const void 	*tmp = addr;

	while (n) {
		size = n;
		if (size > 16)
			size = 16;
		write_addr(addr - tmp);
		write_data(addr, size);
		write_ascii(addr, size);
        if (__screen_offset__ >= 84 * 16) {
            write(
				STDOUT_FILENO,
				__screen__,
				84);
            __screen_offset__ = 0;
        }
        addr += size;
		n -= size;
	}
}

int main(int ac, char *av[])
{
	void 		*map;
	int 		fd;
	struct stat	st;
	
	if (ac < 2)
		return (
			__usage_error(av[1]),
			EXIT_FAILURE);
	if ((__screen__ = malloc(84 * 16)) == NULL)
		return (EXIT_FAILURE);
	if (stat(av[1], &st) == -1
		|| (fd = open(av[1], O_RDONLY)) == -1)
		return (
			free(__screen__),
			EXIT_FAILURE);
	map = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (map == MAP_FAILED)
		return (
			free(__screen__),
			EXIT_FAILURE);

	print_memory(map, st.st_size);
	return (
		munmap(map, st.st_size),
		free(__screen__),
		EXIT_SUCCESS);
}