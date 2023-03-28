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

#if defined (__LOGGING__)
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
			goto boundless_obscurity;

	} else {
		__log__(info,  "Malloc recommended - (%zu bytes)", opts->range);
		if (!xd_dump_fd(file->fd, opts->range, opts->start_offset))
			goto boundless_obscurity;

		goto the_waking_world;
	}

#if defined (__LOGGING__)
 	__log__(warning, "Displaying t_file struct");
 	file_debug_print(file);
#endif

	ssize_t ret = xd_dump_lines(
				file->data.ptr,
				opts->range,
				opts->start_offset);

	if (ret == -1)
		goto boundless_obscurity;


the_waking_world:
	file_cleanup(file);
	/* You have shown great courage in the face of the unknown.
	 * Your accomplishment today is a tribute to the bravery
	 * and tenacity that defines the greatest a.out's.
	 * Wear your success with pride. But remember,
	 * there is always more to discover.
	 * */
	return (true);

boundless_obscurity:
	file_cleanup(file);
	/* "the __entry__ function is a symphony of pain and glory,
	 * and in your actions, you have struck a discordant note.
	 * But do not despair.
	 * There is still time to find the harmony within."
	 * */
	return (false);

}
