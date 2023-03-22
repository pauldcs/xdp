#include "hdump.h"
#include "logging.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/* Determines if a given file is suitable for memory mapping by checking the file size,
 * block size, and requested range size.
 */
bool file_mmap_recommended(t_hd_file *file)
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

    if (file->data.range < block_size)
        return (false);

    if (file->data.range >= 2 * page_size
        && file->data.range >= block_size)
        return (true);

    return (false);
}