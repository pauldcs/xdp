#include "xdp.h"
#include "file.h"
#include "options/user_options.h"
#include "xmem.h"
#include "log.h"
#include <unistd.h>
#include <string.h>

bool file_read_from_offset(t_file *file, size_t range, off_t start_offset)
{
	if (read(file->fd, 0, 0) == -1)
	{
	 	log_message(debug, "%s: read() failed", __FILE__);
	 	return (false);
	}

	if (!xmem_alloc(&file->data.ptr, range))
		return (false);

	file->data.capacity = range;

	if (lseek(file->fd, start_offset, SEEK_SET) == -1)
	{
		log_message(debug, "%s: lseek() failed", __FILE__);
		xmem_free(&file->data.ptr);
		return (false);
	}
	
	if (read(file->fd, file->data.ptr, range) == -1)
	{
		log_message(debug, "%s: read() failed", __FILE__);
		xmem_free(&file->data.ptr);
		return (false);
	}
	return (true);
}