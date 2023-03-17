#include "../incs/hexdump.h"
#include "../incs/libstringf.h"
#include "../incs/reader.h"
#include <unistd.h>
#include <assert.h>
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

/* write a string into __screen__,
 * there is zero checks for overflows,
 * for optimisation reasons, the developer has to make sure 
 * that the string will fit.
 */
static void screen_write_string(const char *str)
{
	while (*str) {
		*(__screen__ + (__screen_offset__)) = *str++;
		__screen_offset__++;
	}
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

/* mimic of the Linux hexdump -C
 */
bool	classic_hexdump_c(const void *addr, size_t n)
{
	size_t		size;
	const void 	*tmp = addr;

	if ((__screen__ = (char *)malloc(79 << 5)) == NULL)
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

unsigned char	*read_data_from_stdin(void)
{
	unsigned char	*line;
	t_reader        r;
	int             ret;

	r.fd = STDIN_FILENO;
	r.save.buf = NULL;
	r.save.size = 0;
	ret = reader(&line, &r, "");
	if (ret == -1)
		return (NULL);
	reader_destroy(&r);
	return (line);
}

int hexdump(t_dump_params *params)
{
	void 		*map;
	int64_t      actual_size;
	int 		fd;
	struct stat	st;

	if (params->is_stdin) {
		if ((map = read_data_from_stdin()) == NULL);
			return (EXIT_FAILURE);
		actual_size = strlen(map);
	} else {
		if (stat(params->filename, &st) == -1)
			return (perror(params->filename), EXIT_FAILURE);
		actual_size = st.st_size;
		if (S_ISDIR(st.st_mode))
			return (fputstr(2, "%s: Is a directory\n", params->filename),
				EXIT_FAILURE);
		if (!S_ISREG(st.st_mode))
			return (fputstr(2, "%s: Is not a regular file\n", params->filename),
				EXIT_FAILURE);
		if ((fd = open(params->filename, O_RDONLY)) == -1)
			return (perror(params->filename), EXIT_FAILURE);
	}

	if (!params->end_offset)
			params->end_offset = actual_size;

	if (params->start_offset || params->end_offset){
		assert(params->start_offset <= params->end_offset
			&& "Start offset comes after the end offset ?");
		assert(params->start_offset <= actual_size
			&& "Start offset comes after EOF");
		assert(params->end_offset <= actual_size
			&& "End offset comes after EOF");
	}

	if (params->max_size) {
		assert(params->max_size < actual_size
			&& "Number of bytes to print exceeds the actual size");
		assert(params->max_size < (params->end_offset - params->start_offset)
			&& "Trying to dump more bytes than available in the range start - end");	
	} else {
		params->max_size = (params->end_offset - params->start_offset);
	}

	if (!params->is_stdin) {
		map = mmap(0, actual_size, PROT_READ, MAP_PRIVATE, fd, 0);
		close(fd);
		if (map == MAP_FAILED)
			return (EXIT_FAILURE);
	}

	char *ptr = (char *)map;
	ptr += params->start_offset;
	
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
		munmap(map, st.st_size);
	else
		free(map);

	return (EXIT_SUCCESS);
}
