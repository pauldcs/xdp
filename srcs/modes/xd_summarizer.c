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

// ssize_t	reader(uint8_t **buf, t_reader *r, char *sep)
// {
// 	size_t	size;
// 	int		ret;

// 	if (!init_buf(r, buf, &size))
// 		return (R_ERROR);
// 	while (!search_char(r, sep, *buf, size))
// 	{
// 		if (size >= r->cap
// 			&& !r_realloc(buf, &r->cap, size, 2 * r->cap))
// 			return (R_ERROR);
// 		ret = read(r->fd, *buf + size, r->cap - size);
// 		if (ret == -1
// 			|| (!ret && !size))
// 			return (free(*buf), R_ERROR);
// 		else if (!ret)
// 			return (size);
// 		size += ret;
// 	}
// 	return (size - r->save.size - 1);
// }

bool xd_summarizer(
	cut8 *addr,
	size_t size,
	size_t offset,
	ut8 *scr_ptr,
	size_t scr_size)
{

	return (true);
}