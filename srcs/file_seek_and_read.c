#include "hexdump.h"
#include "logging.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* Reads a portion of a file into memory and updates the input
 * parameters accordingly.
 */
bool file_seek_and_read(t_dump_params *params)
{
	params->data.capacity = params->file.range_size;
	params->data.data = malloc(params->file.range_size);

	if (params->data.data == NULL) {
		FATAL_ERROR("malloc: %s\n", "Failed to allocate memory");
		return (false);
	}

	if (lseek(params->file.fd, params->file.start_offset, SEEK_SET) == -1) {
		FATAL_ERROR("lseek: %s\n", strerror(errno));
		return (false);
	}
	
	if (read(params->file.fd, params->data.data, params->file.range_size) == -1) {
		FATAL_ERROR("read: %s\n", strerror(errno));
		return (false);
	}

	return (true);
}