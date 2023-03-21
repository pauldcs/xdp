#include "libxdump.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/* Forces to write the buffer fully if write() failes, 
 * it's ok if this ends up looping endlessly.
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
			break ;
		ret += c;
		s -= c;
	}
	return (ret);
}

ssize_t	xd_dump_lines(const uint8_t *addr, size_t n, size_t offset)
{
	uint8_t     *prev = NULL;
	uint8_t     *ptr = (uint8_t *)addr;
	uint8_t     *__scr__;
	size_t      ret = 0;
	size_t      i = 0;


	__scr__ = malloc(DUMP_BUFFER_SIZE);
	if (!__scr__)
		return (-1);

	memset(__scr__, ' ', DUMP_BUFFER_SIZE);

	while (n) {
		if (n >= 16) {
			if (i >= DUMP_BUFFER_SIZE) {
				ret += write_all(1, __scr__, i);
				i ^= i;
			}

			if (prev && *prev == *ptr) {
				if (i && *(uint64_t *)(    prev) == *(uint64_t *)(    ptr)  
					  && *(uint64_t *)(prev + 8) == *(uint64_t *)(ptr + 8)) {
					__scr__[i++] = '+';
					__scr__[i++] = '\n';
					ret += write_all(STDOUT_FILENO, __scr__, i);
					i ^= i;
				}

			} else { 
				i += 2 + xd_pointer_p8_bytes(&__scr__[i], offset);
				i += 2 + xd_data_16_bytes(&__scr__[i], ptr, 16);
				i += xd_ascii_16_bytes(&__scr__[i], ptr, 16);
				__scr__[i++] = '\n';
				prev = ptr;
			}
			n -= 16;

		} else {

			i += 2 + xd_pointer_p8_bytes(&__scr__[i], offset);
			i += 2 + xd_data_16_bytes(&__scr__[i], ptr, n);
			i +=     xd_ascii_16_bytes(&__scr__[i], ptr, n);
		
			__scr__[i++] = '\n';
			n = 0;
		}
		offset += 16;
		ptr += 16;
	}
	ret += write_all(STDOUT_FILENO, __scr__, i);
	return(free(__scr__), ret);
}