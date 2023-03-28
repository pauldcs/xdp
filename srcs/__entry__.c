#include "xdp.h"
#include "log.h"
#include "xtypes.h"
#include "xleaks.h"
#include "options/user_options.h"
#include "log.h"
#include "hex.h"
#include "file.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static void file_cleanup(t_file *file)
{
	(void)file;
	file_destroy(file);
	__xfree__(file);
}

bool __entry__(t_user_options *opts)
{	
	t_file   *file;
	size_t   file_size;

#ifdef __LOGGING__
 	__log__(warning, "Displaying t_user_options struct");
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
		__log__(info, "Mmap recommended - (%zu bytes)", opts->range);
		if (!file_mmap_from_offset(file, opts->range))
		{
			file_cleanup(file);
			return (false);
		}
	} else {
		__log__(info,  "Malloc recommended - (%zu bytes)", opts->range);
		if (!xd_dump_fd(file->fd, opts->range, opts->start_offset))
		{
			file_cleanup(file);
			return (false);
		}
		file_cleanup(file);
		return (true);
	}

#ifdef __LOGGING__
 	__log__(warning, "Displaying t_file struct");
 	file_debug_print(file);
#endif

	ssize_t ret = xd_dump_lines(
				file->data.ptr,
				opts->range,
				opts->start_offset);

	file_cleanup(file);

	if (ret == -1)
		return (false);
	return (true);
}
