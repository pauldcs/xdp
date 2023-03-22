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

bool _entry_(t_hd_opts *opts)
{	
	bool mmaped = false;

	if (!file_try_open(&opts->file)) {
		LOG(ERROR, "file_try_open()");
		return (false);
	}

	if (!sanitize(opts)) {
		LOG(ERROR, "sanitize()");
		return (false);
	}

	if (file_mmap_recommended(&opts->file)) {
		LOG(INFO, "Mmap is recommended");
		if (!file_mmap_from_offset(&opts->file))
			return (false);
		mmaped = true;

	} else {
		LOG(INFO, "Mmap is not recommended");
		if (!file_read_from_offset(&opts->file))
			return (false);
	}

	ssize_t ret = xd_dump_lines(
		opts->file.data.ptr,
		opts->file.data.range,
		opts->file.data.start
	);

	if (mmaped)
		munmap(
			opts->file.data.ptr,
			opts->file.data.bufsize
		);
	else
		free(opts->file.data.ptr);
	
	if (ret == -1)
		return (false);
	return (true);
}
