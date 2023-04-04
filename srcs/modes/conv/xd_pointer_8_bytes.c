#include "hexxer.h"
#include "xtypes.h"
#include <stdint.h>
#include <stddef.h>

size_t	xd_pointer_8_bytes(ut8 *dst, const uintptr_t p)
{
	*(dst + 7) = "0123456789abcdef"[(p >>  0) & 0xf];
	*(dst + 6) = "0123456789abcdef"[(p >>  4) & 0xf];
	*(dst + 5) = "0123456789abcdef"[(p >>  8) & 0xf];
	*(dst + 4) = "0123456789abcdef"[(p >> 12) & 0xf];
	*(dst + 3) = "0123456789abcdef"[(p >> 16) & 0xf];
	*(dst + 2) = "0123456789abcdef"[(p >> 20) & 0xf];
	*(dst + 1) = "0123456789abcdef"[(p >> 24) & 0xf];
	*(dst + 0) = "0123456789abcdef"[(p >> 28) & 0xf];
	return (8);
}