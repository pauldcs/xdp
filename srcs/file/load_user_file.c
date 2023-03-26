#include "file.h"
#include "log.h"
#include "xmem.h"
#include "xtypes.h"
#include <stdbool.h>
#include <stdlib.h>

static void __file_destroy(t_file *file)
{
	file_destroy(file);
	__xfree__(file);
}

t_file *load_user_file(ct8 *filename)
{
	t_file *file = NULL;

	file = __xmalloc__(sizeof(t_file));
	if (!file)
		return (NULL);
	
	file->name = filename;
	if (!file_init(filename, file))
	{
		__file_destroy(file);
		return (NULL);
	}

	if (!file_open_read(filename, &file->fd))
	{
		log_message(debug, "%s: file_open_read() failed", __FILE__);
		__file_destroy(file);
		return (NULL);

	} else {
		log_message(debug, "opened '%s' to fd: %d", filename, file->fd);
		file->open = true;
	}
	return (file);
}