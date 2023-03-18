#include "hexdump.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

bool should_mmap(int fd, size_t file_size, size_t range_size)
{
    size_t 		page_size = sysconf(_SC_PAGE_SIZE);
	struct stat file_info;

    if (range_size >= file_size)
        return (true);

    if (file_size < page_size)
        return (false);

    if (fstat(fd, &file_info) != 0) {
        report_error("fstat: %s\n", strerror(errno)),
		exit(1);
    }
    size_t block_size = file_info.st_blksize;

    if (range_size < block_size)
        return (false);

    if (range_size >= 2 * page_size && range_size >= block_size)
        return (true);

    return (false);
}