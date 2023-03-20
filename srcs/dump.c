#include "hdump.h"
#include "logging.h"
#include "libstringf.h"
#include <sys/mman.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

bool dump(t_dump_params *params)
{
	int ret;

	if (!params->file.filename) {
		params->data.is_mapped = false;
		params->is_stdin = true;

		if (!start_stdin_reader(params)) {
			LOG(ERROR, "start_stdin_reader()");
			return (false);
		}

	} else if (!open_hexable_file(params)) {
		LOG(ERROR, "open_hexable_file()");
		return (false);
	}

	if (!build_dump_structure(params)) {
		LOG(ERROR, "build_dump_structure()");
		return (false);
	}

	if (params->file.filename) {
		if (file_is_mmapabble(
				params->file.fd,
				params->file.file_size,
				params->file.range_size)) {
			params->data.is_mapped = true;
			if (!file_partial_mmap(params)) {
				LOG(ERROR, "file_partial_mmap()");
				return (false);
			}

		} else {
			params->data.is_mapped = false;
			if (!file_seek_and_read(params)) {
				LOG(ERROR, "file_seek_and_read()");
				return (false);
			}
		}
	}

	LOG(INFO, "Parsing: Done");
	LOG(DEBUG, " - data           %p",  params->data.data);
	LOG(DEBUG, " - file_size      %d",  params->file.file_size);
	LOG(DEBUG, " - is_mapped      %s", (params->data.is_mapped ? "true" : "false"));
	LOG(DEBUG, " - aligned_offset %d",  params->data.aligned_offset);
	LOG(DEBUG, " - capacity       %d",  params->data.capacity);
	LOG(DEBUG, " - range_size     %d",  params->file.range_size);
	LOG(DEBUG, " - start_offset   %d",  params->file.start_offset);

	switch (params->mode)
	{
		case DUMP_CLASSIC:
			ret = (params->colored_output ? 
						classic_hexdump_c_color(
							params->data.data,
							params->file.range_size,
							params->file.start_offset
						)
						: classic_hexdump_c(
							params->data.data,
							params->file.range_size,
							params->file.start_offset
						)
				); break;
		
		case DUMP_RAW:
			ret = raw_bytes_dump(
				params->data.data,
				params->file.range_size
			); break;
		
		case DUMP_STRINGS:
			ret = dump_strings(
				params->data.data,
				params->file.range_size,
				params->string_size
			); break;
	}

	write(STDOUT_FILENO, "\n", 1);

	if (params->data.is_mapped)
		munmap(
			params->data.data,
			params->data.capacity
		);
	else
		free(params->data.data);

	return (ret);
}
