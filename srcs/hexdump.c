#include "hexdump.h"
#include "logging.h"
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
		if (!start_stdin_reader(params)) {
			LOG(ERROR, "start_stdin_reader()");
			return (false);
		}
		params->is_stdin = true;

	} else if (!open_hexable_file(params)) {
		LOG(ERROR, "open_hexable_file()");
		return (false);
	}
	if (!build_dump_structure(params)) {
		LOG(ERROR, "build_dump_structure()");
		return (false);
	}
	if (params->filename) {
		if (file_is_mmapabble(
				params->fd,
				params->file_size,
				params->range_size)) {

			params->is_mapped = true;
			if (!file_partial_mmap(params)) {
				LOG(ERROR, "file_partial_mmap()");
				return (false);
			}

		} else {
			params->is_mapped = false;
			if (!file_seek_and_read(params)) {
				LOG(ERROR, "file_seek_and_read()");
				return (false);
			}
		}
	}

	debug_params(params);

	bool ret; 
	switch (params->mode) {
		case DUMP_CLASSIC:
			ret = (params->colored_output ? 
						classic_hexdump_c_color(
							params->data,
							params->range_size)
						: classic_hexdump_c(
							params->data,
							params->range_size)
			);
			break;

		case DUMP_RAW:
			ret = raw_bytes_dump(
				params->data,
				params->range_size);
			break;
	}

	write(STDOUT_FILENO, "\n", 1);

	if (params->is_mapped)
		munmap(params->data, params->capacity);
	else
		free(params->data);

	return (ret);
}
