#include "hexdump.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

bool file_seek_and_read(t_dump_params *params)
{
	params->capacity = params->range_size;
	params->data = malloc(params->range_size);

	if (params->data == NULL)
		return (
			report_error("malloc: %s\n", "Failed to allocate memory"),
			false);

	if (lseek(params->fd, params->start_offset, SEEK_SET) == -1)
		return (
			report_error("lseek: %s\n", strerror(errno)),
			false);
	
	if (read(params->fd, params->data, params->range_size) == -1) 
		return (
			report_error("read: %s\n", strerror(errno)),
			false);

	return (true);
}