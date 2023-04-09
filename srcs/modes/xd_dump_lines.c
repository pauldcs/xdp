
#include "hexxer.h"
#include "utils.h"
#include "xleaks.h"
#include "xtypes.h"
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include <stdio.h>

ssize_t	xd_dump_lines(const ut8 *addr, size_t n, size_t offset, ut8 *scr_ptr, size_t scr_size, bool color)
{
	ut8 *prev = NULL;
	ut8 *ptr = (ut8 *)addr;
	size_t ret = 0;

	ut8 *scr_cursor = scr_ptr;

	bool dump_required = false;
	size_t line_size;

	while (n) {

		if (dump_required) {
			ret += xwrite(
				STDOUT_FILENO,
				scr_ptr,
				scr_cursor - scr_ptr);
			scr_cursor = scr_ptr;
			dump_required = false;
		}

		if (n < 16) {
			line_size = n;
			n = 0;
		
		} else {
			
			if (prev) {
				if (*(uint64_t *)(prev) == *(uint64_t *)(ptr) && 
					*(uint64_t *)(prev + 8) == *(uint64_t *)(ptr + 8)) {
					if (scr_cursor != scr_ptr) {
						*(scr_cursor++) = '+';
						*(scr_cursor++) = '\n';
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

		scr_cursor += xd_pointer_8_bytes(scr_cursor, offset);
		*(scr_cursor++) = ' ';
		*(scr_cursor++) = ' ';
		if (color)
			scr_cursor += xd_data_16_bytes_color(scr_cursor, ptr, line_size);
		else
			scr_cursor += xd_data_16_bytes(scr_cursor, ptr, line_size);
		*(scr_cursor++) = ' ';
		*(scr_cursor++) = ' ';
		scr_cursor += xd_ascii_16_bytes(scr_cursor, ptr, line_size);
		*(scr_cursor++) = '\n';

		if ((size_t)(scr_cursor - scr_ptr) >= scr_size)
			dump_required = true;

		prev = ptr;
		offset += 16;
		ptr += 16;
	}	

	if ((size_t)(scr_cursor - scr_ptr))
		ret += xwrite(STDOUT_FILENO, scr_ptr, scr_cursor - scr_ptr);
	
	return(ret);
}