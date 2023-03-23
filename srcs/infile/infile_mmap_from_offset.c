#include "libs/libstringf.h"
#include "options.h"
#include "debug/logging.h"
#include "hdump.h"
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

/* Maps a portion of a file, aligned to the nearest page boundary,
 * and updates the input parameters accordingly.
 */
bool infile_mmap_from_offset(t_infile *file, size_t range_size)
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
	
	if (file->data.ptr == MAP_FAILED) {
		FATAL_ERROR("mmap: %s", strerror(errno));
		return (false);
	}
	file->data.mapped = true;
	return (true);
}