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
		params->is_mapped = false;
		if (!read_data_from_stdin(params))
			return (report_error(
					"read_data_from_stdin(): Failed\n"),
				false);

		params->is_stdin = true;

	} else if (!safe_open(params)) 
		return (report_error(
				"safe_open(): Failed\n"),
			false);

	if (!build_dump_structure(params))
		return (report_error(
				"build_dump_structure(): Failed\n"),
			false);

	if (params->filename) {
		if (should_use_mmap(
				params->fd,
				params->file_size,
				params->range_size)) {
	
			params->is_mapped = true;
			if (!memory_efficient_mmap(params))
				return (report_error(
						"mem_efficient_mmap(): Failed\n"),
					false);

		} else {
			params->is_mapped = false;
			if (!read_range_only(params))
				return (report_error(
						"read_exact_range(): Failed\n"),
					false);
		}
	}

	debug_params(params);

	switch (params->mode) {
		case DUMP_CLASSIC:
			classic_hexdump_c(
				params->data,
				params->range_size);
			break;

		case DUMP_RAW:
			raw_bytes_dump(
				params->data,
				params->range_size);
			break;
	}

	write(STDOUT_FILENO, "\n", 1);
	
	if (params->is_mapped)
		munmap(params->data, params->capacity);
	else
		free(params->data);

	return (true);
}
