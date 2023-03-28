#include "xleaks.h"
#include <execinfo.h>
#include <stdlib.h>
#include <stddef.h>

#include <stdio.h>

void *malloc_wrapper(size_t size, const char *file, size_t line)
{
	void *ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);

	t_active_rss *rss = active_rss_new_mem(
		false, ptr,
		size, file,
		line);
	
	if (rss == NULL) {
		free(ptr);
		return (NULL);
	}
	active_rss_add(rss);
	return (ptr);
}