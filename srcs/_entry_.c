#include "xdp.h"
#include "log.h"
#include "xtypes.h"
#include "options/user_options.h"
#include "log.h"
#include "string_dump.h"
#include "hex.h"
#include "file.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool _entry_(t_user_options *opts)
{	
	t_file   file;

	if (!file_init(opts->filename, &file))
		return (false);

	if (!user_options_within_range(opts, &file))
	{
		log_message(error, "options_is_ok()");
		return (false);
	}

#ifdef __LOGGING__
 	log_message(warning, "Dumping options struct");
 	user_options_debug_print(opts);
#endif

	if (!file_open_read(opts->filename, &file.fd))
	{
		log_message(error, "infile_open()");
		file_destroy(&file);
		return (false);
	} else {
		log_message(debug, "opened '%s' to fd: %d", file.name, file.fd);
		file.open = true;
	}
	
	if (file_mmap_recommended(&file, opts->range))
	{
		log_message(info, "Mmap recommended - (%zu bytes)", opts->range);
		if (!file_mmap_from_offset(&file, opts->range))
		{
			log_message(fatal, "Failed to malloc the file");
			file_destroy(&file);
			return (false);
		}
	} else {
		log_message(info,  "Malloc recommended - (%zu bytes)", opts->range);
		if (!file_read_from_offset(&file, opts->range, opts->start_offset))
		{
			log_message(fatal, "Failed to malloc the file");
			file_destroy(&file);
			return (false);
		}
	}
#ifdef __LOGGING__
 	log_message(warning, "Dumping final infile struct");
 	file_debug_print(&file);
#endif

	ssize_t ret = -1;
	switch (opts->mode) {
	case M_NORMAL: /* regular hexdump */
		if (!opts->colors) {
			ret = xd_dump_lines(
				file.data.ptr,
				opts->range,
				opts->start_offset);
		}
	break;
	default: break;
	}

	file_destroy(&file);

	if (ret == -1)
		return (false);
	return (true);
}
