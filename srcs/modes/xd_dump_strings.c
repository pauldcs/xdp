#include "hexxer.h"
#include "xtypes.h"
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>

#define MIN_STRING_LEN 4

static size_t	write_all(int fd, const void *buf, size_t s)
{
	ssize_t	c;
	size_t	ret;

	ret = 0;
	while (s)
	{
		c = write(fd, buf + ret, s);
		if (c == -1)
			break ;
		ret += c;
		s -= c;
	}
	return (ret);
}

bool xd_dump_strings(cut8 *addr, size_t n, ut8 *scr_ptr, size_t scr_size)
{
    cut8 *ptr = addr;
    bool dump_required = false;
    size_t count;
    size_t i = 0;
    
    while (n)
    {
        if (dump_required)
        {
			write_all(1, scr_ptr, scr_size);
			dump_required = false;
			i = 0;
		}
        const uint8_t* tmp = ptr;
        count = 0;
        
        while (n
            && XC_PRINT(*ptr)
            && !XC_SPACE(*ptr)
        ) {
            --n;
            ++ptr;
            ++count;
        }
        
        if (count >= MIN_STRING_LEN)
        {
		    i += xd_pointer_p8_bytes(scr_ptr + i, tmp - addr);
            *(scr_ptr + i++) = ':';
            *(scr_ptr + i++) = ' ';
            memcpy(scr_ptr + i, tmp, count);
            i += count;
            *(scr_ptr + i++) = '\n';
        }
        
        while (n 
            && (!XC_PRINT(*ptr)
            || XC_SPACE(*ptr))
        ) {
            --n;
            ++ptr;
        }
		if (i >= scr_size)
			dump_required = true;
    }
	write_all(1, scr_ptr, i);
    return (true);
}