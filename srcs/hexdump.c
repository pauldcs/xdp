#include "hexdump.h"
#include "libstringf.h"
#include <sys/mman.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

bool hexdump(t_dump_params *params)
{
	if (!params->filename) {
		if (!read_data_from_stdin(params))
			return (report_error(
					"read_data_from_stdin(): Failed\n"),
				false);

		params->is_stdin = true;
		params->map_type = MALLOC;

	} else if (!safe_open(params)) 
		return (report_error(
				"safe_open(): Failed\n"),
			false);

	if (!build_dump_structure(params))
		return (report_error(
				"build_dump_structure(): Failed\n"),
			false);

	if (params->filename) {
		if (should_mmap(
				params->fd,
				params->actual_size,
				params->max_size)) {
	
				params->map_type = MMAP;
			if (!mem_efficient_mmap(params))
				return (report_error(
						"mem_efficient_mmap(): Failed\n"),
					false);

		} else {
			params->map_type = MALLOC;
			if (!read_exact_range(params))
				return (report_error(
						"read_exact_range(): Failed\n"),
					false);
		}
	}

	char *ptr = (char *)(params->map);
	//debug_params(params); return (0);

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
		munmap(params->map, params->map_size);
	else
		free(params->map);

	return (true);
}
