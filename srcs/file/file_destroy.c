#include "file.h"
#include "log.h"
#include "xmem.h"
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

void file_destroy(t_file *file)
{
	if (file->open)
	{
		log_message(debug, "Closing file [%d]", file->fd);
		close(file->fd);
	}
	if (file->data.ptr)
	{
		if (file->data.mapped)
		{
			log_message(debug, "Munmapping [%p]", file->data.ptr);
			munmap(
				file->data.ptr,
				file->data.capacity);

		} else {
			log_message(debug, "Freeing [%p]", file->data.ptr);
			xmem_free(file->data.ptr);
		}
	}
	memset(file, 0x00, sizeof(t_file));
}