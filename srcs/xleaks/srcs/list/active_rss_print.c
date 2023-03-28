#include "xleaks.h"
#include <stdio.h>

void active_rss_print(t_active_rss *rss)
{
 	fprintf(stdout,     " - File: %s%s%s:%zu, by process: %d\n",
		C_YELLOW, rss->file, C_RESET,
		rss->line, rss->owner);

    if (rss->type == FILDES)
	{
        fprintf(stdout, "     - File descriptor: %d\n",
			rss->rss.fd);
	
    } else {
        fprintf(stdout, "     - Memory block (%s%p%s -> %s%p%s), size %zub, [%s]\n",
			C_MAGENTA, rss->rss.block.ptr, C_RESET,
			C_MAGENTA, rss->rss.block.ptr + rss->rss.block.size, C_RESET,
			rss->rss.block.size,
			rss->rss.block.map ? "mmap" : "malloc");
    }
	fprintf(stdout, "     - Stack trace:\n");
    for (size_t i = 2; i < rss->bt_size; i++) {
        printf("         - %s\n", rss->backtrace[i]);
    }
}