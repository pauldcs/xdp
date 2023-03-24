#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

bool	xmem_alloc(void **ptr, size_t size)
{
	uint8_t	*s;

	*ptr = malloc(size);
	if (!*ptr)
		return (false);
	return (true);
}