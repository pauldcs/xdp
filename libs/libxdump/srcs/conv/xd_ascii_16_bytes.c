#include "libxdump.h"
#include <stdint.h>
#include <stddef.h>

/* Writes 16 bytes of ascii into __screen__, non printable characters
 * are replaced by '.'
 */
size_t	xd_ascii_16_bytes(uint8_t *dst, const uint8_t *src, size_t n)
{
	size_t	ret = 0;

	if (n >= 16) {
		/*-- 0 - 8 --*/
			dst[0] = _PrintByte[*(src + 0)];
			dst[1] = _PrintByte[*(src + 1)];
			dst[2] = _PrintByte[*(src + 2)];
			dst[3] = _PrintByte[*(src + 3)];
			dst[4] = _PrintByte[*(src + 4)];
			dst[5] = _PrintByte[*(src + 5)];
			dst[6] = _PrintByte[*(src + 6)];
			dst[7] = _PrintByte[*(src + 7)];
		/*-- 8 - 16 --*/
			dst[8]  = _PrintByte[*(src +  8)];
			dst[9]  = _PrintByte[*(src +  9)];
			dst[10] = _PrintByte[*(src + 10)];
			dst[11] = _PrintByte[*(src + 11)];
			dst[12] = _PrintByte[*(src + 12)];
			dst[13] = _PrintByte[*(src + 13)];
			dst[14] = _PrintByte[*(src + 14)];
			dst[15] = _PrintByte[*(src + 15)];
		/*------------*/
		return (16);
	
	} else {
		uint8_t *tmp = (uint8_t *)src;
		while (n--)
			dst[ret++] = _PrintByte[*tmp++];
	}
	return (ret);
}