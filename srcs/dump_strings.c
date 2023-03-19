#include <stdbool.h>
#include "libstringf.h"
#include <ctype.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>

static inline void	write_pointer(const uintptr_t p)
{
	/* Writes a pointer in hex format into __screen__
 	 */
	uint8_t		buffer[12];
	uintptr_t	ptr;
	int			i = 12;

	ptr = (uintptr_t)p;
	buffer[--i] = ' ';
	buffer[--i] = ' ';
	do {
		buffer[--i] = "0123456789abcdef"[ptr & 0xf];
		ptr >>= 4;
	} while (ptr && i);
	while (i)
		buffer[--i] = '.';
	write(1, buffer, 12);
}

bool	dump_strings(const uint8_t *addr, size_t n, size_t len)
{
	uint8_t *ptr = (uint8_t *)addr;
	uint8_t *tmp = ptr;
	size_t count;
	
	while (n)
	{
		count = 0;
		while (n-- && isprint(*++ptr))
			count++;
		if (count > len)
		{
			write_pointer((uintptr_t)(ptr - tmp));
			write(1, ptr - count, count);
			write(1, "\n", 1);
		}
	}
	return (true);
}