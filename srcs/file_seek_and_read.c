#include "hexdump.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

bool file_seek_and_read(t_dump_params *params)
{
	params->data.capacity = params->file.range_size;
	params->data.data = malloc(params->file.range_size);

	if (params->data.data == NULL)
		return (
			report_error("malloc: %s\n", "Failed to allocate memory"),
			false);

	if (lseek(params->file.fd, params->file.start_offset, SEEK_SET) == -1)
		return (
			report_error("lseek: %s\n", strerror(errno)),
			false);
	
	if (read(params->file.fd, params->data.data, params->file.range_size) == -1) 
		return (
			report_error("read: %s\n", strerror(errno)),
			false);

	return (true);
}