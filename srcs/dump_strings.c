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

bool dump_strings(const uint8_t* addr, size_t n, size_t len)
{
    const uint8_t* ptr = addr;
    const uint8_t* end = addr + n;
    
    while (ptr < end)
    {
        size_t count = 0;
        const uint8_t* tmp = ptr;
        
        while (ptr < end && isprint(*ptr)) {
            ++ptr;
            ++count;
        }
        
        if (count > len) {
            write_pointer((uintptr_t)(tmp - addr));
            write(1, tmp, count);
            write(1, "\n", 1);
        }
        
        while (ptr < end && !isprint(*ptr))
            ++ptr;
    }
    return (true);
}