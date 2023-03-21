#include "libxdump.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

# define  LINE_LEN (77 + 1)
# define   N_LINES 512
# define DUMP_SIZE ((LINE_LEN) * N_LINES)

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

ssize_t	xd_dump_lines(const uint8_t *addr, size_t n, size_t offset, bool color)
{
	size_t (*_print_ptr_func)
			(uint8_t *, const uintptr_t) = {
		&xd_pointer_p8_bytes
	}; 

	size_t (*_print_data_func[2])
			(uint8_t *, const uint8_t *, size_t
			) = {
			(color) ? 
				&xd_data_16_bytes_color :
				&xd_data_16_bytes,
			&xd_ascii_16_bytes
	}; 

	uint8_t     *prev = NULL;
	uint8_t     *scr = malloc(DUMP_SIZE);
	uint8_t     *ptr = (uint8_t *)addr;
	size_t      size = 0;
	size_t      idx = 0;

	if (!scr)
		return (-1);

	memset(scr, 0x20, DUMP_SIZE);

	while (n) {
		if (n >= 16) {
			if (idx >= DUMP_SIZE) {
				size += write_all(1, scr, idx);
				idx = 0;
			}
			if (prev
				&& *(uint64_t *)(    prev) == *(uint64_t *)(    ptr)  
				&& *(uint64_t *)(prev + 8) == *(uint64_t *)(ptr + 8)) {
				if (idx) {
					scr[idx++] = '+';
					scr[idx++] = '\n';
					size += write_all(1, scr, idx) - 2;
					idx = 0;
				}
			} else { 
				idx += _print_ptr_func(scr + idx, offset) + 2;
				idx += _print_data_func[0](scr + idx, ptr, 16) + 2;
				idx += _print_data_func[1](scr + idx, ptr, 16);
				prev = ptr;
				scr[idx++] = '\n';
			}
			n -= 16;

		} else {

			idx += _print_ptr_func(scr + idx, offset) + 2;
			idx += _print_data_func[0](scr + idx, ptr, n) + 2;
			idx += _print_data_func[1](scr + idx, ptr, n);
			scr[idx++] = '\n';
			n = 0;
		}
		offset += 16;
		ptr += 16;
	}
	size += write_all(1, scr, idx);
	return(free(scr), size);
}