#include "log.h"
#include "xtypes.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

bool	xmem_alloc(ptr_t *ptr, size_t size)
{
	*ptr = malloc(size);
	if (!ptr)
		return (true);

	log_message(fatal, "xmem_alloc: Failed to allocate %zu bytes", size);
	return (true);
}