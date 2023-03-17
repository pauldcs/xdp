#include "hexdump.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

static char    *__screen__;
static int     __screen_offset__ = 0;

/*  Forces to write the buffer fully if write() failes, 
 *	it's ok if this ends up looping endlessly.
 */
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

/* dump the current content in __screen__
 */
static void print_screen(void)
{
	write_all(STDOUT_FILENO,
		__screen__,
		__screen_offset__);
	__screen_offset__ = 0;
}

/* writes a pointer in hex format into the __screen__
 */
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

/* write 16 bytes of data into __screen__, each byte separed by a space
 */
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

/* write 16 bytes in ascii into __screen__, if the bytes is 
 * non printable, it writes a '.' instead
 */
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

/* write the bytes as a stream without any formatting. Null bytes are 
 * replaced by ".." and the whole thing is dumped with one write()
*/
bool raw_bytes_dump(const void *addr, size_t size)
{
	char	*ptr = (char *)addr;

	if ((__screen__ = (char *)malloc(size * 2 + 1)) == NULL)
		return (false);
	while (size--)
	{
		*(__screen__ + (__screen_offset__++)) = BASE[(*ptr >> 4) & 0xf];
		*(__screen__ + (__screen_offset__++)) = BASE[*ptr & 0xf];
		ptr++;
	}
	*(__screen__ + (__screen_offset__++)) = '\n';
	print_screen();
	free(__screen__);
	return (true);
}

/* mimic of the Linux hexdump -C
 */
bool	classic_hexdump_c(const void *addr, size_t n)
{
	size_t		size;
	const void 	*tmp = addr;

	if ((__screen__ = (char *)malloc(79 << 7)) == NULL)
		return (false);
	while (n) {
		size = (n > 16 ? 16 : n);
		if (tmp != addr
			&& *((uint64_t *)(addr - 4)) == *((uint64_t *)addr)
    		&& *((uint64_t *)(addr - 3)) == *((uint64_t *)addr + 1)
    		&& *((uint64_t *)(addr - 2)) == *((uint64_t *)addr + 2)
    		&& *((uint64_t *)(addr - 1)) == *((uint64_t *)addr + 3)
		) {
			if (__screen_offset__) {
				*(__screen__ + (__screen_offset__++)) = '*';
				*(__screen__ + (__screen_offset__++)) = '\n';
				print_screen();
			}
		} else {
        	if (__screen_offset__ >= 78 << 7)
				print_screen();
			write_pointer((uintptr_t)(addr - tmp), 10);
			*(__screen__ + (__screen_offset__++)) = ':';
			*(__screen__ + (__screen_offset__++)) = ' ';
			*(__screen__ + (__screen_offset__++)) = ' ';
			write_16_bytes_spaced(addr, size);
			*(__screen__ + (__screen_offset__++)) = ' ';
			write_16_ascii(addr, size);
			*(__screen__ + (__screen_offset__++)) = '\n';
		}
        addr += size;
		n -= size;
	}
    if (__screen_offset__)
		print_screen();
	free(__screen__);
	return(true);
}

bool hexdump(t_dump_params *params)
{
	if (!handle_parameters(params))
		return (false);
	if (!params->is_stdin) {

		params->map = mmap(
				0,
				params->actual_size,
				PROT_READ,
				MAP_PRIVATE,
				params->fd,
				0);
	
		close(params->fd);
		if (params->map == MAP_FAILED)
			return (false);
	}

	char *ptr = (char *)(params->map + params->start_offset);
	
	switch (params->mode) {
		case DUMP_CLASSIC:
			classic_hexdump_c(ptr, params->max_size);
			break;
		case DUMP_RAW:
			raw_bytes_dump(ptr, params->max_size);
			break;
	}

	write(1, "\n", 1);

	if (!params->is_stdin)
		munmap(params->map, params->actual_size);
	else
		free(params->map);

	return (true);
}
