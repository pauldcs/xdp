#include "xleaks.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>

t_active_rss *active_rss_new_mem(
	bool       map,
	void       *ptr,
	size_t     size,
	const char *file,
	size_t     line)
{
	t_active_rss *rss = malloc(sizeof(t_active_rss));
	if (rss == NULL)
		return (NULL);

	bzero(rss, sizeof(t_active_rss));

	rss->owner          = getpid();
	rss->file           = file;
	rss->line           = line;
	rss->type           = MEMORY;
	rss->rss.block.map  = map;
	rss->rss.block.ptr  = ptr;
	rss->rss.block.size = size;
	
	return (rss);
}