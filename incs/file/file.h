#ifndef __FILE_H__
# define __FILE_H__

#include "hdump.h"
#include <stddef.h>

bool file_is_mmapabble(int fd, size_t file_size, size_t range_size);
bool file_partial_mmap(t_dump_params *params);
bool file_seek_and_read(t_dump_params *params);
ssize_t file_try_open(const char *filename, int *fd);

#endif /* __FILE_H__ */