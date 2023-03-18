#include "hexdump.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

bool read_exact_range(t_dump_params *params)
{
	params->map_size = params->max_size;
	params->map = malloc(params->max_size);

	if (params->map == NULL)
		return (
			report_error("malloc: %s\n", "Failed to allocate memory"),
			false);

	if (lseek(params->fd, params->start_offset, SEEK_SET) == -1)
		return (
			report_error("lseek: %s\n", strerror(errno)),
			false);
	
	if (read(params->fd, params->map, params->max_size) == -1) 
		return (
			report_error("read: %s\n", strerror(errno)),
			false);
			
	return (true);
}