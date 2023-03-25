#include "xtypes.h"
#include "../../../incs/xdp.h"
#include <stdint.h>
#include <stddef.h>

#ifdef 0
size_t	xd_data_16_bytes_color(cut8 *addr, size_t n, ut8 *buffer)
{
	ut8 	*tmp = buffer;
	ut8 	*ptr = (ut8 *)addr;
	size_t 	pad;

	n = (n < 16 ? 16 : n);
	pad = 16 - n;

	while (n) {
		if (_CharColor[*ptr] == CYAN) { 
			*(ut64 *)(buffer) = *(ut64 *)CYN;
			buffer += 8;
			while (n && _CharColor[*ptr] == CYAN) {
				*(ut16 *)(buffer) = _B16Pair[*ptr++];
				buffer += 2;
				if (--n)
					*(buffer++) = ' ';
			}
		} else if (_CharColor[*ptr] == WHITE) {
			*(ut64*)(buffer) = *(ut64 *)LGR;
			buffer += 8;
			while (n && _CharColor[*ptr] == WHITE) {
				*(ut32 *)(buffer) = _B16Pair[*ptr++];
				buffer += 2;
				if (--n)
					*(buffer++) = ' ';
			}
		} else {
			if (!*ptr) {
				*(ut64 *)(buffer) = *(ut64 *)GRY;
				buffer += 6;
				while (n && !*ptr) {
					*(ut32*)(buffer) = _B16Pair[*ptr++];
					buffer += 2;
					if (--n)
						*(buffer++) = ' ';
				}
			}
		}
	}
	*(ut64 *)(buffer) = END_UINT64;
	buffer += 5;
	while (pad--) {
		*(ut32 *)(buffer) = *(ut32 *)"   ";
		buffer += 3;
	}
	return (buffer - tmp);
}
#endif