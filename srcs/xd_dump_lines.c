
#include "hex.h"
#include "xleaks.h"
#include "xtypes.h"
#include <stddef.h>
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

ssize_t	xd_dump_lines(const ut8 *addr, size_t n, size_t offset, ut8 *__scr_ptr, size_t scr_size)
{
	ut8 *prev = NULL;
	ut8 *ptr = (ut8 *)addr;
	size_t __scr_off = 0;
	size_t ret = 0;

	memset(__scr_ptr, ' ', scr_size);

	bool dump_required = false;
	size_t line_size;

	while (n) {	

		if (dump_required) {
			ret += write_all(
				STDOUT_FILENO,
				__scr_ptr,
				__scr_off);
			__scr_off = 0;
			dump_required = false;
		}

		if (n < 16) {
			line_size = n;
			n = 0;
		
		} else {
			if (prev) {
				if (*(uint64_t *)(    prev) == *(uint64_t *)(    ptr) && 
					*(uint64_t *)(prev + 8) == *(uint64_t *)(ptr + 8)) {
					if (__scr_off) {
						*(__scr_ptr + __scr_off++) = '+';
						*(__scr_ptr + __scr_off++) = '\n';
						dump_required = true;
					} 
					offset += 16;
					ptr += 16;
					n -= 16;
					continue;
				}
			}
			line_size = 16;
			n -= 16;
		}

		__scr_off += xd_pointer_p8_bytes(__scr_ptr + __scr_off, offset) + 2;
		__scr_off += xd_data_16_bytes(__scr_ptr + __scr_off, ptr, line_size) + 2;
		__scr_off += xd_ascii_16_bytes(__scr_ptr + __scr_off, ptr, line_size);
		*(__scr_ptr + __scr_off++) = '\n';

		if (__scr_off >= scr_size)
			dump_required = true;

		prev = ptr;
		offset += 16;
		ptr += 16;
	}	

	if (__scr_off)
		ret += write_all(STDOUT_FILENO, __scr_ptr, __scr_off);
	
	return(ret);
}