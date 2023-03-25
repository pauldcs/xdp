#include "file.h"
#include "debug/logging.h"
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>

void file_destroy(t_file *file)
{
	if (file->open)
	{
		__log(Debug, "Closing file [%d]", file->fd);
		close(file->fd);
	}
	if (file->data.ptr)
	{
		if (file->data.mapped)
		{
			__log(Debug, "Munmapping [%p]", file->data.ptr);
			munmap(
				file->data.ptr,
				file->data.capacity);

		} else {
			__log(Debug, "Freeing [%p]", file->data.ptr);
			free(file->data.ptr);
		}
	}
	memset(file, 0x00, sizeof(t_file));
}