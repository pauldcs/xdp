#include <stdbool.h>
#include "libstringf.h"
#include <ctype.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>

static inline void	write_pointer(const uintptr_t p)
{
	uint8_t		buffer[12];
	uintptr_t	ptr;
	int			i = 12;

	ptr = (uintptr_t)p;
    i -= 3;
    *(uint32_t *)(buffer + i) = *(uint32_t *)":  ";
    do {
		buffer[--i] = "0123456789abcdef"[ptr & 0xf];
		ptr >>= 4;
	} while (ptr && i);
	while (i)
		buffer[--i] = '0';
	write(1, buffer, 12);
}

/* Scans memory for printable ASCII characters and writes any found strings
 * longer than len to standard output.
 */
bool dump_strings(const uint8_t* addr, size_t n, size_t len)
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
            write_pointer(tmp - addr);
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