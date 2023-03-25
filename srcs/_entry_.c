#include "xdp.h"
#include "xtypes.h"
#include "options.h"
#include "debug/logging.h"
#include "string_dump.h"
#include "hexdump.h"
#include "file.h"
#include <stdbool.h>
#include <string.h>

bool _entry_(t_user_options *opts)
{	
	t_file   file;

	if (!file_init(opts->filename, &file))
		return (false);

#ifdef __LOGGING__
	__log(Warning, "Dumping infile struct");
	file_debug_print(&file);
#endif /* if __LOGGING__ */

	if (!options_within_range(opts, &file))
	{
		__log(Error, "options_is_ok()");
		return (false);
	}

#ifdef __LOGGING__
	__log(Warning, "Dumping options struct");
	options_debug_print(opts);
#endif /* if __LOGGING__ */

	if (!file_open_read(opts->filename, &file.fd))
	{
		__log(Error, "infile_open()");
		file_destroy(&file);
		return (false);
	} else
		__log(Debug, "opened '%s' to fd: %d", file.name, file.fd);
	
	if (file_mmap_recommended(&file, opts->range))
	{
		__log(Info, "Mmap recommended - (%zu bytes)", opts->range);
		if (!file_mmap_from_offset(&file, opts->range))
		{
			FATAL_ERROR("Failed to malloc the file");
			file_destroy(&file);
			return (false);
		}
	} else {
		__log(Info, "Malloc recommended - (%zu bytes)", opts->range);
		if (!file_read_from_offset(&file, opts->range, opts->start_offset))
		{
			FATAL_ERROR("Failed to malloc the file");
			file_destroy(&file);
			return (false);
		}
	}

#ifdef __LOGGING__
	__log(Warning, "Dumping final infile struct");
	file_debug_print(&file);
#endif /* if __LOGGING__ */

	ssize_t ret = -1;

	switch (opts->mode) {
	case M_NORMAL: /* regular hexdump */
		if (!opts->colors) {
			ret = xd_dump_lines(
				file.data.ptr,
				opts->range,
				opts->start_offset);
		} else
			FATAL_ERROR("Colorized dump is not implemented"); break ;
		/* else {
			ret = xd_dump_lines_color(
				file.data.ptr,
				opts->range,
				opts->start_offset);
		} */
		break;
	case M_STRING: /* dump ascii strings */
		ret = string_dump(
			file.data.ptr,
			opts->range,
			opts->string_size);
		break;
	case M_STREAM: /* not implemented */
		break;
	default:
		break;
	}


	file_destroy(&file);

	if (ret == -1)
		return (false);
	return (true);
}
