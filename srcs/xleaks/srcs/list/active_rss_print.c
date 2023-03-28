#include "xleaks.h"
#include <stdio.h>
#include <unistd.h>

void print_with_space(const char *str) {
    size_t len = strlen(str);
    int in_word = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
            if (in_word) {
                write(1, " ", 1);
                in_word = 0;
            }
        } else {
            write(1, &str[i], 1);
            in_word = 1;
        }
    }
    write(1, "\n", 1);
}

void active_rss_print(t_active_rss *rss)
{
 	fprintf(stdout,     " - File: %s%s%s:%zu, by process: %d\n",
		C_YELLOW, rss->file, C_RESET,
		rss->line, rss->owner);

    if (rss->type == FILDES)
	{
        fprintf(stdout, "    - File descriptor: %d\n",
			rss->rss.fd);
	
    } else {
        fprintf(stdout, "    - Memory block (%s%p%s -> %s%p%s), size %zub, [%s]\n",
			C_MAGENTA, rss->rss.block.ptr, C_RESET,
			C_MAGENTA, rss->rss.block.ptr + rss->rss.block.size, C_RESET,
			rss->rss.block.size,
			rss->rss.block.map ? "mmap" : "malloc");
    }
	fprintf(stdout, "    - Backtrace:\n");
    for (size_t i = 2; i < rss->bt_size; i++) {
		write(1, "       - ", 10);
        print_with_space(rss->backtrace[i]);
		if (i == rss->bt_size - 1)
			write(1, "\n", 1);
    }
}