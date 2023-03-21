#include <stdint.h>
#include <stddef.h>

# define BASE16_ASCII_CHARS "0123456789abcdef"

size_t	copy_pointer_64(const uintptr_t p, uint8_t *buffer)
{
	*(buffer + 7) = BASE16_ASCII_CHARS[(p >>  0) & 0xf];
	*(buffer + 6) = BASE16_ASCII_CHARS[(p >>  4) & 0xf];
	*(buffer + 5) = BASE16_ASCII_CHARS[(p >>  8) & 0xf];
	*(buffer + 4) = BASE16_ASCII_CHARS[(p >> 12) & 0xf];
	*(buffer + 3) = BASE16_ASCII_CHARS[(p >> 16) & 0xf];
	*(buffer + 2) = BASE16_ASCII_CHARS[(p >> 20) & 0xf];
	*(buffer + 1) = BASE16_ASCII_CHARS[(p >> 24) & 0xf];
	*(buffer + 0) = BASE16_ASCII_CHARS[(p >> 28) & 0xf];
	return (8);
}