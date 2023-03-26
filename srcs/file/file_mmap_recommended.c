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

    log_message(debug, "page_size: %zu", page_size);

    if (file->size < page_size)
        return (false);

    if (fstat(file->fd, &file_info) != 0)
    {
        log_message(fatal,  "fstat: failed");
		return (false);
    }

    size_t block_size = file_info.st_blksize;

    log_message(debug, "block_size: %zu", block_size);

    if (range_size < block_size)
        return (false);

    if (range_size >= 2 * page_size
        && range_size >= block_size)
    {
        log_message(debug, "The file should be mmapped");
        return (true);
    }

    log_message(debug, "Malloc is sufficient for loading memory");
    return (false);
}