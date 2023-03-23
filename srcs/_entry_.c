#include "xdp.h"
#include "options.h"
#include "debug/logging.h"
#include "libs/libxdump.h"
#include "infile.h"
#include <stdbool.h>
#include <string.h>

bool _entry_(t_user_options *opts)
{	
	t_infile   file;

	memset(&file, 0, sizeof(file));
	file.name = opts->filename;

	if (!infile_get_size(&file)) {
		__log(Error, "infile_try_open()");
		return (false);
	}

#ifdef __LOGGING__
	__log(Warning, "Dumping infile struct");
    infile_struct_debug_print(&file);
#endif /* if __LOGGING__ */

	if (!options_within_range(opts, &file)) {
		__log(Error, "options_is_ok()");
		return (false);
	}

#ifdef __LOGGING__
	__log(Warning, "Dumping options struct");
	options_struct_debug_print(opts);
#endif /* if __LOGGING__ */

	if (!infile_open(&file)) {
		__log(Error, "infile_open()");
		return (false);
	} else
		__log(Debug, "opened '%s' to fd: %d", file.name, file.fd);
	
	if (infile_mmap_recommended(&file, opts->range)) {
		__log(Info, "Mmap recommended");
		if (!infile_mmap_from_offset(&file, opts->range)) {
			FATAL_ERROR("Failed to malloc the file");
			infile_close(&file);
			return (false);
		}
	} else {
		__log(Info, "Malloc recommended");
		if (!infile_read_from_offset(&file, opts->range, opts->start_offset)) {
			FATAL_ERROR("Failed to malloc the file");
			return (false);
		}
	}

#ifdef __LOGGING__
	__log(Warning, "Dumping final infile struct");
    infile_struct_debug_print(&file);
#endif /* if __LOGGING__ */

	ssize_t ret = xd_dump_lines(
		file.data.ptr,
		opts->range,
		opts->start_offset
	);

	infile_destroy(&file);

	if (ret == -1)
		return (false);
	return (true);
}
