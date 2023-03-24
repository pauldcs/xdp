#include <stdbool.h>
#include "xtypes.h"
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>

static inline void	write_offset(const uintptr_t p)
{
	uint8_t		buffer[10];

	*(buffer + 9) = ' ';
	*(buffer + 8) = ' ';
	*(buffer + 7) = "0123456789abcdef"[((uintptr_t)p >>  0) & 0xf];
	*(buffer + 6) = "0123456789abcdef"[((uintptr_t)p >>  4) & 0xf];
	*(buffer + 5) = "0123456789abcdef"[((uintptr_t)p >>  8) & 0xf];
	*(buffer + 4) = "0123456789abcdef"[((uintptr_t)p >> 12) & 0xf];
	*(buffer + 3) = "0123456789abcdef"[((uintptr_t)p >> 16) & 0xf];
	*(buffer + 2) = "0123456789abcdef"[((uintptr_t)p >> 20) & 0xf];
	*(buffer + 1) = "0123456789abcdef"[((uintptr_t)p >> 24) & 0xf];
	*(buffer + 0) = "0123456789abcdef"[((uintptr_t)p >> 28) & 0xf];

    write(STDOUT_FILENO, buffer, 10);
}

bool str_dump(const uint8_t* addr, size_t n, size_t len)
{
    const uint8_t   *ptr = addr;
    size_t          count;
    
    while (n)
    {
        const uint8_t* tmp = ptr;
        count = 0;
        
        while (n && XC_PRINT(*ptr)
                && !XC_SPACE(*ptr))
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
        
        while (n && (!XC_PRINT(*ptr) || XC_SPACE(*ptr)))
        {
            --n;
            ++ptr;
        }
    }
    return (true);
}