#include "hdump.h"
#include "file/file.h"
#include "options.h"
#include "logging.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* Reads a portion of a file into memory and updates the input
 * parameters accordingly.
 */
bool file_read_from_offset(t_hd_file *file)
{
	if (read(file->fd, 0, 0) == -1) {
		FATAL_ERROR("read(): %s", strerror(errno));
		return (false);
	}

	if (file->data.range > 400 * 1024 * 1024) {
		FATAL_ERROR("Too much memory needed (More than 400MB)");
		return (false);
	}
	
	if (file->data.range > 200 * 1024 * 1024) {
		LOG(WARNING, "Allocating more than 200MB");
	}

	file->data.ptr = malloc(file->data.range);

	if (file->data.ptr == NULL) {
		FATAL_ERROR("malloc(): %s\n", "Failed to allocate memory");
		return (false);
	}

	file->data.bufsize = file->data.range;

	if (file->data.start
		&& lseek(file->fd, file->data.start, SEEK_SET) == -1) {
		FATAL_ERROR("lseek(): %s\n", strerror(errno));
		return (false);
	}
	
	if (read(file->fd, file->data.ptr, file->data.range) == -1) {
		FATAL_ERROR("read: %s\n", strerror(errno));
		return (false);
	}

	return (true);
}