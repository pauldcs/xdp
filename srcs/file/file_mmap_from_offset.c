#include "options/user_options.h"
#include "log.h"
#include "xdp.h"
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

bool file_mmap_from_offset(t_file *file, size_t range_size)
{
	size_t aligned_offset = file->data.start & ~(sysconf(_SC_PAGE_SIZE) - 1);

	file->data.start = (file->data.start - aligned_offset);
	file->data.capacity = range_size + file->data.start;

	file->data.ptr = mmap(
			NULL,
			range_size,
	 		PROT_READ,
	 		MAP_PRIVATE | MAP_FILE,
	 		file->fd,
			aligned_offset);
	
	if (file->data.ptr == MAP_FAILED)
	{
		__log__(fatal,  "mmap: %s", strerror(errno));
		return (false);
	}
	file->data.mapped = true;
	return (true);
}