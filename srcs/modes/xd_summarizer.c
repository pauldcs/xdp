#include "xtypes.h"
#include "utils.h"
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>

// static inline size_t distance_cmp(const char *s1, const char *s2, size_t n)
// {
//     size_t d = 0;
// 	for (;n--;s1++ && s2++)
//     	d += __builtin_popcount(*s1 ^ *s2);
//     return (d);
// }


// TODO
bool xd_summarizer(
	cut8 *addr,
	size_t size,
	size_t offset,
	ut8 *scr_ptr,
	size_t scr_size)
{
	ut8	*ptr = (ut8 *)addr;
    bool dump_required = false;
    size_t i = 0;

    (void)offset;
	while (size--)
	{
        if (dump_required)
        {
			xwrite(1, scr_ptr, scr_size);
			dump_required = false;
			i = 0;
		}
        *(scr_ptr + (i++)) = "0123456789abcdef"[(*ptr >> 4) & 0xf];
		*(scr_ptr + (i++)) = "0123456789abcdef"[*ptr & 0xf];
		ptr++;
		if (i >= scr_size)
			dump_required = true;
	}
	xwrite(1, scr_ptr, i);
	return (true);
}