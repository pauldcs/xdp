#include "xdp.h"
#include "log.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

bool file_mmap_recommended(t_file *file, size_t range_size)
{
    size_t page_size = sysconf(_SC_PAGE_SIZE);
    size_t block_size = file->st.st_blksize;

    if (file->size < page_size)
        return (false);

    if (range_size < block_size)
        return (false);

    if (range_size >= 2 * page_size
        && range_size >= block_size)
        return (true);

    return (false);
}