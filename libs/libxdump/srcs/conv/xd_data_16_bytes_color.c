#include "libxdump.h"
#include <stdint.h>
#include <stddef.h>

size_t	xd_data_16_bytes_color(const uint8_t *addr, size_t n, uint8_t *buffer)
{
	uint8_t 	*tmp = buffer;
	uint8_t 	*ptr = (uint8_t *)addr;
	size_t 		pad;

	n = (n < 16 ? 16 : n);
	pad = 16 - n;

	while (n) {
		if (_CharColor[*ptr] == CYAN) { 
			*(uint64_t*)(buffer) = CYN_UINT64;
			buffer += 8;
			while (n && _CharColor[*ptr] == CYAN) {
				*(uint16_t*)(buffer) = _B16Pair[*ptr++];
				buffer += 2;
				if (--n)
					*(buffer++) = ' ';
			}
		} else if (_CharColor[*ptr] == WHITE) {
			*(uint64_t*)(buffer) = END_UINT64;
			buffer += 5;
			while (n && _CharColor[*ptr] == WHITE) {
				*(uint32_t*)(buffer) = _B16Pair[*ptr++];
				buffer += 2;
				if (--n)
					*(buffer++) = ' ';
			}
		} else {
			if (!*ptr) {
				*(uint64_t*)(buffer) = GRY_UINT64;
				buffer += 8;
				while (n && !*ptr) {
					*(uint32_t*)(buffer) = _B16Pair[*ptr++];
					buffer += 2;
					if (--n)
						*(buffer++) = ' ';
				}
			}
		}
	}
	*(uint64_t*)(buffer) = END_UINT64;
	buffer += 5;
	while (pad--) {
		*(uint32_t*)(buffer) = *(uint32_t*)"   ";
		buffer += 3;
	}
	return (buffer - tmp);
}