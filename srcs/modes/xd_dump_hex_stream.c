#include "xtypes.h"
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>

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

bool xd_dump_hex_stream(cut8 *addr, size_t size, size_t offset, ut8 *scr_ptr, size_t scr_size)
{
	ut8	*ptr = (ut8 *)addr;
    bool dump_required = false;
    size_t i = 0;

    (void)offset;
	while (size--)
	{
        if (dump_required)
        {
			write_all(1, scr_ptr, scr_size);
			dump_required = false;
			i = 0;
		}
        *(scr_ptr + (i++)) = "0123456789abcdef"[(*ptr >> 4) & 0xf];
		*(scr_ptr + (i++)) = "0123456789abcdef"[*ptr & 0xf];
		ptr++;
		if (i >= scr_size)
			dump_required = true;
	}
	write_all(1, scr_ptr, i);
	return (true);
}