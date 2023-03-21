#include "libxdump.h"
#include <stdint.h>
#include <stddef.h>

#define BLK_UINT64 *(uint64_t*)"\e[0;30m"
#define RED_UINT64 *(uint64_t*)"\e[0;31m"
#define GRN_UINT64 *(uint64_t*)"\e[0;32m"
#define YEL_UINT64 *(uint64_t*)"\e[0;33m"
#define BLU_UINT64 *(uint64_t*)"\e[0;34m"
#define MAG_UINT64 *(uint64_t*)"\e[0;35m"
#define CYN_UINT64 *(uint64_t*)"\e[0;36m"
#define WHT_UINT64 *(uint64_t*)"\e[0;37m"
#define GRY_UINT64 *(uint64_t*)"\x1b[2;37m"
#define END_UINT64 *(uint64_t*)"\e[0m"

size_t	xd_data_16_bytes_color(uint8_t *dst, const uint8_t *src, size_t n)
{
	uint8_t 	*tmp = dst;
	uint8_t 	*ptr = (uint8_t *)src;
	size_t 		pad;

	n = (n > 16 ? 16 : n);
	pad = 16 - n;

	while (n) {
		if (xd_isprint(*ptr)) { 
			*(uint64_t*)(dst) = CYN_UINT64;
			dst += 8;
			while (n && xd_isprint(*ptr)) {
				*(uint16_t*)(dst) = _PrintByte[*ptr++];
				dst += 3;
				--n;
			}
		} else {
			if (!*ptr) { 
				*(uint64_t*)(dst) = GRY_UINT64;
				dst += 8;
				while (n && !*ptr) {
					*(uint16_t*)(dst) = _PrintByte[*ptr++];
					dst += 3;
					--n;
				}
			} else { 
				*(uint64_t*)(dst) = END_UINT64;
				dst += 5;
				while (n && *ptr && !xd_isprint(*ptr)) {
					*(uint16_t*)(dst) = _PrintByte[*ptr++];
					dst += 3;
					--n;
				}
			}
		}
	}
	*(uint64_t*)(dst) = END_UINT64;
	dst += 5;
	while (pad--) {
		*(uint16_t*)(dst) = 0x2020;
		dst += 3;
	}
	return (dst - tmp);
}