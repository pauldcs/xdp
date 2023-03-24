#include "xtypes.h"
#include "xdp.h"
#include "hexdump.h"
#include <stdint.h>
#include <stddef.h>

size_t	xd_data_16_bytes(uint8_t *dst, const uint8_t *src, size_t n)
{
	if (n >= 16) {
		/*-- 0 - 8 --*/
			*(uint16_t*)(dst +  0) = _B16Pair[*(src + 0)];
			*(uint16_t*)(dst +  3) = _B16Pair[*(src + 1)];
			*(uint16_t*)(dst +  6) = _B16Pair[*(src + 2)];
			*(uint16_t*)(dst +  9) = _B16Pair[*(src + 3)];
			*(uint16_t*)(dst + 12) = _B16Pair[*(src + 4)];
			*(uint16_t*)(dst + 15) = _B16Pair[*(src + 5)];
			*(uint16_t*)(dst + 18) = _B16Pair[*(src + 6)];
			*(uint16_t*)(dst + 21) = _B16Pair[*(src + 7)];
		/*-- 8 - 16 --*/
			*(uint16_t*)(dst + 24) = _B16Pair[*(src +  8)];
			*(uint16_t*)(dst + 27) = _B16Pair[*(src +  9)];
			*(uint16_t*)(dst + 30) = _B16Pair[*(src + 10)];
			*(uint16_t*)(dst + 33) = _B16Pair[*(src + 11)];
			*(uint16_t*)(dst + 36) = _B16Pair[*(src + 12)];
			*(uint16_t*)(dst + 39) = _B16Pair[*(src + 13)];
			*(uint16_t*)(dst + 42) = _B16Pair[*(src + 14)];
			*(uint16_t*)(dst + 45) = _B16Pair[*(src + 15)];
		/*------------*/
		return (47);

	} else {

		uint8_t 	*ptr = (uint8_t *)src;
		uint8_t 	*tmp = dst;
		size_t 		pad = (16 - n) * 3;

		if (pad)
			pad--;
	
		while (n--) {
			*(uint16_t*)(dst) = _B16Pair[*ptr++];
			dst += 3;
		}
		return (dst - tmp + pad);
	}
	return (0);
}