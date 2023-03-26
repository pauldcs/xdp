#include "log.h"
#include "xtypes.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

bool	xmem_alloc(ptr_t *addr, size_t size)
{
	if ((*addr = malloc(size)))
	{
		bzero(*addr, size);
		return (true);
	}
	log_message(fatal, "xmem_alloc: Failed to allocate %zu bytes", size);
	return (false);
}