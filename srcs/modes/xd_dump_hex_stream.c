#include <stdbool.h>


bool xd_dump_hex_stream(const void *addr, size_t size)
{
	uint8_t	*ptr = (uint8_t *)addr;

	if ((__screen__ = (uint8_t *)malloc((size << 1) + 1)) == 0)
		return (false);
	while (size--)
	{
		*(__screen__ + (__screen_offset__++)) = "0123456789abcdef"[(*ptr >> 4) & 0xf];
		*(__screen__ + (__screen_offset__++)) = "0123456789abcdef"[*ptr & 0xf];
		ptr++;
	}
	*(__screen__ + (__screen_offset__++)) = '\n';
	__dump_screen();
	free(__screen__);
	return (true);
}