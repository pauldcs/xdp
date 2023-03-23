#include "xdp.h"
#include "infile.h"
#include "options.h"
#include "debug/logging.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

bool infile_read_from_offset(t_infile *file, size_t range, off_t start_offset)
{
	if (read(file->fd, 0, 0) == -1) {
	 	FATAL_ERROR("read(): %s", strerror(errno));
	 	return (false);
	 }

	 if (range > 400 * 1024 * 1024) {
	 	FATAL_ERROR("Too much memory needed (More than 400MB)");
	 	return (false);
	 }
	
	 if (range > 200 * 1024 * 1024) {
	 	__log(Warning, "Allocating more than 200MB");
	 }

	 file->data.ptr = malloc(range);

	 if (file->data.ptr == NULL) {
	 	FATAL_ERROR("malloc(): %s\n", "Failed to allocate memory");
	 	return (false);
	 }

	 file->data.capacity = range;

	 if (lseek(file->fd, start_offset, SEEK_SET) == -1) {
	 	FATAL_ERROR("lseek(): %s\n", strerror(errno));
		free(file->data.ptr);
	 	return (false);
	 }
	
	 if (read(file->fd, file->data.ptr, range) == -1) {
	 	FATAL_ERROR("read: %s\n", strerror(errno));
		free(file->data.ptr);
	 	return (false);
	 }
	return (true);
}