#include "hex.h"
#include "xmem.h"
#include "xdp.h"
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

ssize_t	xd_dump_lines_color(const uint8_t *addr, size_t n, size_t offset)
{
	uint8_t     *prev = NULL;
	uint8_t     *ptr = (uint8_t *)addr;
	uint8_t     *__scr_ptr = NULL;
	size_t      __scr_off = 0;
	size_t      ret = 0;
	size_t size = SCREEN_BUFFER_SIZE + (16 * 8 + 16 * 5) + 32;


	if (!xmem_alloc((ptr_t *)&__scr_ptr, size))
		return (-1);

	(void)memset(__scr_ptr, ' ', SCREEN_BUFFER_SIZE);

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
		//*(uint64_t*)(__scr_ptr + __scr_off) = *(uint64_t *)WHT;
		//__scr_off+=8;
		__scr_off += xd_pointer_p8_bytes(
				__scr_ptr + __scr_off,
				offset);
		//*(uint64_t*)(__scr_ptr + __scr_off) = END_UINT64;
		//__scr_off+=5;
	
		*(uint16_t *)(__scr_ptr + __scr_off) = *(uint16_t *)"  ";
		__scr_off += 2;
		__scr_off += xd_data_16_bytes_color(
				ptr,
				line_size,
				__scr_ptr + __scr_off);

		*(uint16_t *)(__scr_ptr + __scr_off) = *(uint16_t *)"  ";
		__scr_off += 2;
		__scr_off += xd_ascii_16_bytes(
				__scr_ptr + __scr_off,
				ptr,
				line_size);

		*(__scr_ptr + __scr_off++) = '\n';
	
		if (__scr_off >= size)
			dump_required = true;

		prev = ptr;
		offset += 16;
		ptr += 16;
	}

	if (__scr_off)
		ret += write_all(STDOUT_FILENO, __scr_ptr, __scr_off);
	
	return(xmem_free(__scr_ptr), ret);
}