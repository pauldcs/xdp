#include "hexdump.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

static char    *__screen__;
static int     __screen_offset__ = 0;

static size_t	write_all(int fd, const void *buf, size_t s)
{
	/* Forces to write the buffer fully if write() failes, 
     * it's ok if this ends up looping endlessly.
     */
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

static void __dump_screen(void)
{
	/* Dumps the content of __screen__ to stdout
	 */
	write_all(STDOUT_FILENO,
		__screen__,
		__screen_offset__);
	__screen_offset__ = 0;
}

static inline void	write_pointer(const uintptr_t p, size_t width)
{
	/* Writes a pointer in hex format into __screen__
 	 */
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
	/* Writes 16 bytes of data into __screen__, each byte separed by a space
 	 */
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
	/* Writes 16 bytes of ascii into __screen__, non printable characters
 	 * are replaced by '.'
 	 */
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

static bool raw_bytes_dump(const void *addr, size_t size)
{
	/* write the bytes as a stream without any formatting. Null bytes are 
 	 * replaced by ".."
	 */
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
	__dump_screen();
	free(__screen__);
	return (true);
}

static bool	classic_hexdump_c(const void *addr, size_t n)
{
	/* mimic of the Linux hexdump -C
 	*/
	size_t		size;
	uint64_t 	*ptr;
	const void 	*tmp = addr;

	if ((__screen__ = (char *)malloc(79 << 7)) == NULL)
		return (false);
	while (n) {
		size = (16 < n ? 16 : n);
		ptr = (uint64_t *)addr;
		if (tmp != addr
    		&& *(ptr - 2) == *(ptr + 0)
    		&& *(ptr - 1) == *(ptr + 1)

		) {
			if (__screen_offset__) {
				*(__screen__ + (__screen_offset__++)) = '*';
				*(__screen__ + (__screen_offset__++)) = '\n';
				__dump_screen();
			}
		} else {
        	if (__screen_offset__ >= 78 << 7)
				__dump_screen();
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
		__dump_screen();
	free(__screen__);
	return(true);
}

bool hexdump(t_dump_params *params)
{
	if (!prepare_params_struct(params))
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
