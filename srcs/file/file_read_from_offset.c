#include "xdp.h"
#include "file.h"
#include "options/user_options.h"
#include "log.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

bool file_read_from_offset(t_file *file, size_t range, off_t start_offset)
{
	if (read(file->fd, 0, 0) == -1)
	{
	 	log_message(fatal,  "read(): %s", strerror(errno));
	 	return (false);
	}

	if (range > 400 * 1024 * 1024)
	{
		log_message(fatal,  "Too much memory needed (More than 400MB)");
		return (false);
	}
	
	if (range > 200 * 1024 * 1024)
	{
		log_message(warning, "Allocating more than 200MB");
	}

	file->data.ptr = malloc(range);

	if (file->data.ptr == NULL)
	{
		log_message(fatal,  "malloc(): %s\n", "Failed to allocate memory");
		return (false);
	}

	file->data.capacity = range;

	if (lseek(file->fd, start_offset, SEEK_SET) == -1)
	{
		log_message(fatal,  "lseek(): %s\n", strerror(errno));
	free(file->data.ptr);
		return (false);
	}
	
	if (read(file->fd, file->data.ptr, range) == -1)
	{
		log_message(fatal,  "read: %s\n", strerror(errno));
	free(file->data.ptr);
		return (false);
	}
	return (true);
}