#include "hex.h"
#include <stdint.h>
#include <stddef.h>

size_t	xd_pointer_8_bytes(uint8_t *dst, const uintptr_t p)
{
	*(dst + 7) = BASE16_ASCII_CHARS[(p >>  0) & 0xf];
	*(dst + 6) = BASE16_ASCII_CHARS[(p >>  4) & 0xf];
	*(dst + 5) = BASE16_ASCII_CHARS[(p >>  8) & 0xf];
	*(dst + 4) = BASE16_ASCII_CHARS[(p >> 12) & 0xf];
	*(dst + 3) = BASE16_ASCII_CHARS[(p >> 16) & 0xf];
	*(dst + 2) = BASE16_ASCII_CHARS[(p >> 20) & 0xf];
	*(dst + 1) = BASE16_ASCII_CHARS[(p >> 24) & 0xf];
	*(dst + 0) = BASE16_ASCII_CHARS[(p >> 28) & 0xf];
	return (8);
}