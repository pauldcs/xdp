#include <stdbool.h>
#include <stddef.h>
#include <string.h>

bool	re_alloc(void **buf, size_t *cap, size_t len, size_t new_cap)
{
	void	*new_buf;

	if (!alloc(&new_buf, new_cap))
		return (false);
	memcpy(new_buf, *buf, len);
	free(*buf);
	*buf = new_buf;
	*cap = new_cap;
	return (true);
}