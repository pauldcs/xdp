#include "hdump.h"
#include "options.h"
#include "logging.h"
#include "libstringf.h"
#include "libxdump.h"
#include "file/file.h"
#include <sys/mman.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

bool _entry_(t_dump_params *params)
{
	int ret;

	if (!params->file.filename) {
		LOG(ERROR, "No input file");
			return (false);

	} else {
		ssize_t ret = file_try_open(
				params->file.filename,
				&params->file.fd
		);
		if (ret == -1) {
			LOG(ERROR, "open_hexable_file()");
			return (false);
		}
		params->file.file_size = ret;
	}

	if (!sanitize(params)) {
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

	LOG(INFO, "Dumping now");
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
			ret = xd_dump_lines(
					params->data.data,
					params->file.range_size,
					params->file.start_offset,
					false)
			; break;
		
		case DUMP_RAW: ret = 0; break ;
		//	ret = perform_raw_hexdump(
		//		params->data.data,
		//		params->file.range_size
		//	); break;
		
		case DUMP_STRINGS: ret = 0; break ;
		// ret = perform_string_dump(
		// 	params->data.data,
		// 	params->file.range_size,
		// 	params->string_size
		// ); break;
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
