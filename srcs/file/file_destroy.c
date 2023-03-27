#include "file.h"
#include "log.h"
#include "xmem.h"
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>

void file_destroy(t_file *file)
{
	if (file->open)
	{
		__log__(debug, "Closing file [%d]", file->fd);
		close(file->fd);
	}
	if (file->data.ptr)
	{
		if (file->data.mapped)
		{
			__log__(debug, "Munmapping [%p]", file->data.ptr);
			munmap(
				file->data.ptr,
				file->data.capacity);

		} else {
			__log__(debug, "Freeing [%p]", file->data.ptr);
			__xfree__(file->data.ptr);
		}
	}
	memset(file, 0xff, sizeof(t_file));
}