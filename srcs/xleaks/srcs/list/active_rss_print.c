#include "xleaks.h"
#include <stdio.h>

void active_rss_print(t_active_rss *rss)
{
 	fprintf(stdout,     "\n - File: %s%s%s:%zu, (un)responsable process: %d\n",
		C_YELLOW, rss->file, C_RESET,
		rss->line, rss->owner);

    if (rss->type == FILDES)
	{
        fprintf(stdout, "     - File descriptor: %d\n",
			rss->rss.fd);
	
    } else {
        fprintf(stdout, "     - Memory block (%s%p%s -> %s%p%s) is leaking %zub, [%s]\n",
			C_MAGENTA, rss->rss.block.ptr, C_RESET,
			C_MAGENTA, rss->rss.block.ptr + rss->rss.block.size, C_RESET,
			rss->rss.block.size,
			rss->rss.block.map ? "mmap" : "malloc");
    }
}