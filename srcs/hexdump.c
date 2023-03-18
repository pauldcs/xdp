#include "hexdump.h"
#include "libstringf.h"
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

bool hexdump(t_dump_params *params)
{
	if (!prepare_params_struct(params))
		return (false);

	size_t map_size = (
		params->end_offset ? 
			params->end_offset :
			params->actual_size
	);

	if (params->map_type == MMAP) {
		params->map = mmap(
				0, map_size,
		 		PROT_READ | PROT_WRITE,
		 		MAP_PRIVATE | MAP_FILE,
		 		params->fd, 0);
	
		if (params->map == MAP_FAILED)
			return (
				report_error("mmap: %s\n", strerror(errno)),
				close(params->fd),
				false);

		close(params->fd);

	} else if (!params->is_stdin) {
		params->map = malloc(params->max_size);

		if (params->map == NULL)
			return (
				report_error("malloc: %s\n", "Failed to allocated memory"),
				close(params->fd),
				false);

		if (lseek(params->fd, params->start_offset, SEEK_SET) == -1)
			return (
				report_error("lseek: %s\n", strerror(errno)),
				close(params->fd),
				false);
		
		if (read(params->fd, params->map, params->max_size) == -1) 
			return (
				report_error("read: %s\n", strerror(errno)),
				close(params->fd),
				false);

		close(params->fd);
	}

	char *ptr = (char *)(params->map);
	
	switch (params->mode) {
		case DUMP_CLASSIC:
			classic_hexdump_c(
				ptr + params->start_offset,
				params->max_size);
			break;

		case DUMP_RAW:
			raw_bytes_dump(
				ptr + params->start_offset,
				params->max_size);
			break;
	}

	write(1, "\n", 1);
	
	if (params->map_type == MMAP)
		munmap(params->map, map_size);
	else
		free(params->map);

	return (true);
}
