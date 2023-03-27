#include "xdp.h"
#include "log.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

bool file_mmap_recommended(t_file *file, size_t range_size)
{
    size_t 		page_size = sysconf(_SC_PAGE_SIZE);
	struct stat file_info;

    __log__(debug, "page_size: %zu", page_size);

    if (file->size < page_size)
        return (false);

    if (fstat(file->fd, &file_info) != 0)
    {
        __log__(fatal,  "fstat: failed");
		return (false);
    }

    size_t block_size = file_info.st_blksize;

    __log__(debug, "block_size: %zu", block_size);

    if (range_size < block_size)
        return (false);

    if (range_size >= 2 * page_size
        && range_size >= block_size)
    {
        __log__(debug, "The file should be mmapped");
        return (true);
    }

    __log__(debug, "Malloc is sufficient for loading memory");
    return (false);
}