#include "xdp.h"
#include "log.h"
#include "xtypes.h"
#include "xmem.h"
#include "options/user_options.h"
#include "log.h"
#include "hex.h"
#include "file.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static void __file_destroy(t_file *file)
{
	file_destroy(file);
	__xfree__(file);
}

bool _entry_(t_user_options *opts)
{	
	t_file   *file;
	size_t   file_size;

#ifdef __LOGGING__
 	log_message(warning, "Displaying t_user_options struct");
 	user_options_debug_print(opts);
#endif

	if (!opts->filename)
		return (xd_dump_fd(0, opts->range, opts->start_offset));

	if (!file_exists(opts->filename)
		|| !file_get_size(opts->filename, &file_size)
		|| !user_options_within_range(opts, file_size))
		return (false);

	file = load_user_file(opts->filename);
	
	if (file_mmap_recommended(file, opts->range))
	{
		log_message(info, "Mmap recommended - (%zu bytes)", opts->range);
		if (!file_mmap_from_offset(file, opts->range))
		{
			__file_destroy(file);
			return (false);
		}
	} else {
		log_message(info,  "Malloc recommended - (%zu bytes)", opts->range);
		if (!xd_dump_fd(file->fd, opts->range, opts->start_offset))
		{
			__file_destroy(file);
			return (false);
		}
		__file_destroy(file);
		return (true);
	}

#ifdef __LOGGING__
 	log_message(warning, "Displaying t_file struct");
 	file_debug_print(file);
#endif

	ssize_t ret = xd_dump_lines(
				file->data.ptr,
				opts->range,
				opts->start_offset);

	__file_destroy(file);

	if (ret == -1)
		return (false);
	return (true);
}
