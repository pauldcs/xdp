/* Writes a offset in hex format into __screen__
 */

#include "libxdump.h"
#include <stdint.h>
#include <stddef.h>

size_t	inline xd_pointer_p8_bytes(uint8_t *dst, const uintptr_t p)
{
	uintptr_t 	ptr = (uintptr_t)p;

	*(dst + 8) = BASE16_ASCII_CHARS[(ptr >>  0) & 0xf];
	*(dst + 7) = BASE16_ASCII_CHARS[(ptr >>  4) & 0xf];
	*(dst + 6) = BASE16_ASCII_CHARS[(ptr >>  8) & 0xf];
	*(dst + 5) = BASE16_ASCII_CHARS[(ptr >> 12) & 0xf];
	*(dst + 4) = BASE16_ASCII_CHARS[(ptr >> 16) & 0xf];
	*(dst + 3) = BASE16_ASCII_CHARS[(ptr >> 20) & 0xf];
	*(dst + 2) = BASE16_ASCII_CHARS[(ptr >> 24) & 0xf];
	*(dst + 1) = BASE16_ASCII_CHARS[(ptr >> 28) & 0xf];
	*(dst + 0) = '0';

	int i = 0;
	while ((ptr >>= 4))
		i++;
	*(dst + 7 - i) = '+';
	return (9);
}