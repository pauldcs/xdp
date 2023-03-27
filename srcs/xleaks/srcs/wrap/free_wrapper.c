#include "xleaks.h"
#include <stdlib.h>
#include <stddef.h>

void free_wrapper(void *ptr, const char *file, size_t line)
{
	(void)file;
	(void)line;
	active_rss_delete(ptr, MEMORY);
	free(ptr);
}