#include "libstringf.h"
#include "logging.h"
#include "hdump.h"
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

/* Maps a portion of a file, aligned to the nearest page boundary,
 * and updates the input parameters accordingly.
 */
bool file_mmap_from_offset(t_hd_file *file)
{
	size_t aligned_offset = file->data.start & ~(sysconf(_SC_PAGE_SIZE) - 1);

	file->data.start = (file->data.start - aligned_offset);
	file->data.bufsize =file->data.range + file->data.start;

	file->data.ptr = mmap(
			NULL,
			file->data.bufsize,
	 		PROT_READ,
	 		MAP_PRIVATE | MAP_FILE,
	 		file->fd,
			aligned_offset);
	
	if (file->data.ptr == MAP_FAILED) {
		FATAL_ERROR("mmap: %s", strerror(errno));
		return (false);
	}
	return (true);
}