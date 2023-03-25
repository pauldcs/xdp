#include "memory.h"
#include "log.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

bool	xmem_realloc(ptr_t *buf, size_t *cap, size_t len, size_t new_cap)
{
	void	*new_buf;

	if (!xmem_alloc(&new_buf, new_cap)) {
		log_message(fatal, "xmem_realloc: Failed to allocate %zu bytes", new_cap);
		return (false);
	}
	memcpy(new_buf, *buf, len);
	free(*buf);
	*buf = new_buf;
	*cap = new_cap;
	return (true);
}