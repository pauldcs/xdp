#include "xleaks.h"
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>

void active_rss_add(t_active_rss *rss)
{
	t_active_rss *tmp = xleak_trace.list;

	switch (rss->type)
	{
		case MEMORY:
			xleak_trace.n_allocs++;
			xleak_trace.n_bytes += rss->rss.block.size;
			xleak_trace.in_use.n_blocks++;
			xleak_trace.in_use.n_bytes += rss->rss.block.size;
			break;
		
		case FILDES:
			xleak_trace.in_use.n_fds++;
			break;
	}

	if (xleak_trace.list == NULL) {
		xleak_trace.list = rss;
		return;
	}

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = rss;
}