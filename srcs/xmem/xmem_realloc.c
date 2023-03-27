#include "xmem.h"
#include "xtypes.h"
#include "log.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

ptr_t	xmem_realloc(ptr_t *buf, size_t *cap, size_t len, size_t new_cap)
{
	void	*new_buf = __xmalloc__(new_cap);

	if (!new_buf) {
		__log__(fatal, "xmem_realloc: Failed to allocate %zu bytes", new_cap);
		return (NULL);
	}
	memcpy(new_buf, *buf, len);
	__xfree__(*buf);
	*buf = new_buf;
	*cap = new_cap;
	return (new_buf);
}