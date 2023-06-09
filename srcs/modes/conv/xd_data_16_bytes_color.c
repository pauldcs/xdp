#include "xtypes.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

# define RED     0x00000001
# define GREEN   0x00000010
# define YELLOW  0x00000100
# define BLUE    0x00001000
# define MAGENTA 0x00010000
# define CYAN    0x00100000
# define WHITE   0x01000000
# define GREY    0x10000000

size_t xd_data_16_bytes_color(ut8 *buffer, cut8 *addr, size_t n)
{
	ut8 	*tmp = buffer;
	ut8 	*ptr = (ut8 *)addr;
	size_t 	pad;

	n = (n > 16 ? 16 : n);
	pad = 16 - n;
	while (n) {
		if (_CharColor[*ptr] == CYAN) { 
			//*(ut64 *)(buffer) = *(ut64 *)C_CYAN;
			__builtin_memcpy(buffer, "\e[0;36m", sizeof("\e[0;36m"));
			buffer += 7;
			while (n && _CharColor[*ptr] == CYAN) {
				*(ut32 *)(buffer) = _B16Pair[*ptr++];
				buffer += 2;
				if (--n)
					*(buffer++) = ' ';
			}
		} else if (_CharColor[*ptr] == WHITE) {
			//*(ut64*)(buffer) = *(ut64 *)C_RESET;
			__builtin_memcpy(buffer, "\e[0m", sizeof("\e[0m"));
			buffer += 4;
			while (n && _CharColor[*ptr] == WHITE) {
				*(ut32 *)(buffer) = _B16Pair[*ptr++];
				buffer += 2;
				if (--n)
					*(buffer++) = ' ';
			}
		} else {
			if (!*ptr) {
				//*(ut64 *)(buffer) = *(ut64 *)"\033[90m";
				__builtin_memcpy(buffer, "\033[90m", sizeof("\033[90m"));
				buffer += 5;
				while (n && !*ptr) {
					*(ut32*)(buffer) = _B16Pair[*ptr++];
					buffer += 2;
					if (--n)
						*(buffer++) = ' ';
				}
			}
		}
	}
	//*(ut64 *)(buffer) = *(ut64 *)C_RESET;
	__builtin_memcpy(buffer, "\e[0m", sizeof("\e[0m"));
	buffer += 4;
	while (pad--) {
		*(ut32 *)(buffer) = *(ut32 *)"   ";
		buffer += 3;
	}
	return (buffer - tmp);
}