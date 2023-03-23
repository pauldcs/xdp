#include "hdump.h"
#include <stdbool.h>
#include "libs/libstringf.h"
#include <ctype.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>

static inline void	write_offset(const uintptr_t p)
{
	uint8_t		buffer[11];
	uintptr_t 	ptr = (uintptr_t)p;

    *(buffer + 10) = ' ';
    *(buffer + 9) = ' ';
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
    write(1, buffer, 11);
}

/* Scans memory for printable ASCII characters and writes any found strings
 * longer than len to standard output.
 */
bool xd_string_dump(const uint8_t* addr, size_t n, size_t len)
{
    const uint8_t   *ptr = addr;
    size_t          count;
    
    while (n)
    {
        const uint8_t* tmp = ptr;
        count = 0;
        
        while (n && isprint(*ptr)) {
            --n;
            ++ptr;
            ++count;
        }
        
        if (count > len) {
            write_offset(tmp - addr);
            write(1, tmp, count);
            write(1, "\n", 1);
        }
        
        while (n && !isprint(*ptr)) {
            --n;
            ++ptr;
        }
    }
    return (true);
}