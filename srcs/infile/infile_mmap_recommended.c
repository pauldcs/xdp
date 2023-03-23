#include "xdp.h"
#include "debug/logging.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

bool infile_mmap_recommended(t_infile *file, size_t range_size)
{
    size_t 		page_size = sysconf(_SC_PAGE_SIZE);
	struct stat file_info;

    if (file->size < page_size)
        return (false);

    if (fstat(file->fd, &file_info) != 0) {
        FATAL_ERROR("fstat: failed");
		return (false);
    }
    size_t block_size = file_info.st_blksize;

    if (range_size < block_size)
        return (false);

    if (range_size >= 2 * page_size
        && range_size >= block_size)
        return (true);

    return (false);
}