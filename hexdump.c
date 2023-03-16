#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SCREEN_LINE_SIZE 79
#define BASE "0123456789abcdef"

static char 	*__screen__;
static int 		__screen_offset__ = 0;

static inline void	write_addr(const uintptr_t p)
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
	*(int32_t *)(buffer + 10)= 0x20203a;
	__screen_offset__ += 13;
}

static inline void	write_data(const void *addr, size_t size)
{
	char	*buffer = (__screen__ + __screen_offset__);
	char	*ptr;
	size_t  i;

	i = 0;
	ptr = (char *)addr;
	while (size-- && i < 49) {
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
	while (i < 49)
		buffer[i++] = ' ';
	__screen_offset__ += i;
}

static inline void	write_ascii(const void *s, size_t size)
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
	buffer[i++] = '\n';
	__screen_offset__ += i;
}

static inline void dump_screen(void)
{
	write (STDOUT_FILENO,
		__screen__,
		__screen_offset__);
	__screen_offset__ = 0;
}

static void	print_memory(const void *addr, size_t n)
{
	size_t		size;
	const void 	*tmp = addr;

	while (n) {
		size = (n > 16 ? 16 : n);
		if (tmp != addr && !memcmp(addr - 16, addr, 16)) {
			if (__screen_offset__) {
				dump_screen();
				write (STDOUT_FILENO, "<snip>\n", 7);
			}
		} else {
			write_addr(addr - tmp);
			write_data(addr, size);
			write_ascii(addr, size);
        	if (__screen_offset__ >= SCREEN_LINE_SIZE << 5)
				dump_screen();
		}
        addr += size;
		n -= size;
	}
    if (__screen_offset__)
		dump_screen();
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
			free(__screen__),
			EXIT_FAILURE);
	map = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (map == MAP_FAILED)
		return (
			free(__screen__),
			EXIT_FAILURE);

	print_memory(map, st.st_size);
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
		write (STDERR_FILENO, "Error: Usage\n", 14);
		return (EXIT_FAILURE);
	}
	while (--ac)
		ret = hexdump(*++av);
	return (ret);
}