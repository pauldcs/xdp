/* Writes a offset in hex format into __screen__
 */

#include <stdint.h>
#include <stddef.h>

# define BASE16_ASCII_CHARS "0123456789abcdef"

size_t	copy_pointer_64_plus(const uintptr_t p, uint8_t *buffer)
{
	uintptr_t 	ptr = (uintptr_t)p;

	*(buffer + 8) = BASE16_ASCII_CHARS[(ptr >>  0) & 0xf];
	*(buffer + 7) = BASE16_ASCII_CHARS[(ptr >>  4) & 0xf];
	*(buffer + 6) = BASE16_ASCII_CHARS[(ptr >>  8) & 0xf];
	*(buffer + 5) = BASE16_ASCII_CHARS[(ptr >> 12) & 0xf];
	*(buffer + 4) = BASE16_ASCII_CHARS[(ptr >> 16) & 0xf];
	*(buffer + 3) = BASE16_ASCII_CHARS[(ptr >> 20) & 0xf];
	*(buffer + 2) = BASE16_ASCII_CHARS[(ptr >> 24) & 0xf];
	*(buffer + 1) = BASE16_ASCII_CHARS[(ptr >> 28) & 0xf];
	*(buffer + 0) = '0';

	int i = 0;
	while ((ptr >>= 4))
		i++;
	*(buffer + 7 - i) = '+';
	return (9);
}