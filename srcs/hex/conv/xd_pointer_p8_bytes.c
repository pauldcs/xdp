#include "xtypes.h"
#include <stdint.h>
#include <stddef.h>

size_t	xd_pointer_p8_bytes(ut8 *dst, const uintptr_t p)
{
	uintptr_t 	ptr = (uintptr_t)p;

	*(dst + 8) = "0123456789abcdef"[(ptr >>  0) & 0xf];
	*(dst + 7) = "0123456789abcdef"[(ptr >>  4) & 0xf];
	*(dst + 6) = "0123456789abcdef"[(ptr >>  8) & 0xf];
	*(dst + 5) = "0123456789abcdef"[(ptr >> 12) & 0xf];
	*(dst + 4) = "0123456789abcdef"[(ptr >> 16) & 0xf];
	*(dst + 3) = "0123456789abcdef"[(ptr >> 20) & 0xf];
	*(dst + 2) = "0123456789abcdef"[(ptr >> 24) & 0xf];
	*(dst + 1) = "0123456789abcdef"[(ptr >> 28) & 0xf];
	*(dst + 0) = '0';

	/* add '+' to the hex number */
	int i = 0;
	while ((ptr >>= 4))
		i++;
	*(dst + 7 - i) = '+';
	return (9);
}