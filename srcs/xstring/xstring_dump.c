#include <stdbool.h>
#include "libs/libstringf.h"
#include "libs/libxdump.h"
#include "xstring.h"
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>

static inline void	write_offset(const uintptr_t p)
{
	uint8_t		buffer[10];

	*(buffer + 9) = ' ';
	*(buffer + 8) = ' ';
	*(buffer + 7) = BASE16_ASCII_CHARS[((uintptr_t)p >>  0) & 0xf];
	*(buffer + 6) = BASE16_ASCII_CHARS[((uintptr_t)p >>  4) & 0xf];
	*(buffer + 5) = BASE16_ASCII_CHARS[((uintptr_t)p >>  8) & 0xf];
	*(buffer + 4) = BASE16_ASCII_CHARS[((uintptr_t)p >> 12) & 0xf];
	*(buffer + 3) = BASE16_ASCII_CHARS[((uintptr_t)p >> 16) & 0xf];
	*(buffer + 2) = BASE16_ASCII_CHARS[((uintptr_t)p >> 20) & 0xf];
	*(buffer + 1) = BASE16_ASCII_CHARS[((uintptr_t)p >> 24) & 0xf];
	*(buffer + 0) = BASE16_ASCII_CHARS[((uintptr_t)p >> 28) & 0xf];

    write(STDOUT_FILENO, buffer, 10);
}

bool xstring_dump(const uint8_t* addr, size_t n, size_t len)
{
    const uint8_t   *ptr = addr;
    size_t          count;
    
    while (n)
    {
        const uint8_t* tmp = ptr;
        count = 0;
        
        while (n && xd_isprint(*ptr)
                && !xd_isspace(*ptr))
        {
            --n;
            ++ptr;
            ++count;
        }
        
        if (count > len)
        {
            write_offset(tmp - addr);
            write(1, tmp, count);
            write(1, "\n", 1);
        }
        
        while (n && (!xd_isprint(*ptr) || xd_isspace(*ptr)))
        {
            --n;
            ++ptr;
        }
    }
    return (true);
}