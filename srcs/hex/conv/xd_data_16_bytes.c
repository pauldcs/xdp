#include "xtypes.h"
#include "xdp.h"
#include "hex.h"
#include <stdint.h>
#include <stddef.h>

size_t xd_data_16_bytes(cut8 *dst, cut8 *src, size_t n)
{
	if (n >= 16) {
		/*-- 0 - 8 --*/
			*(ut16 *)(dst +  0) = _B16Pair[*(src + 0)];
			*(ut16 *)(dst +  3) = _B16Pair[*(src + 1)];
			*(ut16 *)(dst +  6) = _B16Pair[*(src + 2)];
			*(ut16 *)(dst +  9) = _B16Pair[*(src + 3)];
			*(ut16 *)(dst + 12) = _B16Pair[*(src + 4)];
			*(ut16 *)(dst + 15) = _B16Pair[*(src + 5)];
			*(ut16 *)(dst + 18) = _B16Pair[*(src + 6)];
			*(ut16 *)(dst + 21) = _B16Pair[*(src + 7)];
		/*-- 8 - 16 --*/
			*(ut16 *)(dst + 24) = _B16Pair[*(src +  8)];
			*(ut16 *)(dst + 27) = _B16Pair[*(src +  9)];
			*(ut16 *)(dst + 30) = _B16Pair[*(src + 10)];
			*(ut16 *)(dst + 33) = _B16Pair[*(src + 11)];
			*(ut16 *)(dst + 36) = _B16Pair[*(src + 12)];
			*(ut16 *)(dst + 39) = _B16Pair[*(src + 13)];
			*(ut16 *)(dst + 42) = _B16Pair[*(src + 14)];
			*(ut16 *)(dst + 45) = _B16Pair[*(src + 15)];
		/*------------*/
		return (47);

	} else {

		ut8 	*ptr = (ut8 *)src;
		cut8 	*tmp = dst;
		ut64 	pad = (16 - n) * 3;

		if (pad)
			pad--;
	
		while (n--) {
			*(ut16 *)(dst) = _B16Pair[*ptr++];
			dst += 3;
		}
		return (dst - tmp + pad);
	}
	return (0);
}