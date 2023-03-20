#include "libstringf.h"
#include "logging.h"
#include "hexdump.h"
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

/* Maps a portion of a file, aligned to the nearest page boundary,
 * and updates the input parameters accordingly.
 */
bool file_partial_mmap(t_dump_params *params)
{
	params->data.aligned_offset = params->file.start_offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
	params->file.start_offset = (params->file.start_offset - params->data.aligned_offset);
	params->data.capacity = params->file.range_size + params->file.start_offset;

	params->data.data = mmap(
			NULL,
			params->data.capacity,
	 		PROT_READ | PROT_WRITE,
	 		MAP_PRIVATE | MAP_FILE,
	 		params->file.fd,
			params->data.aligned_offset);
	
	if (params->data.data == MAP_FAILED) {
		FATAL_ERROR("fstat: failed");
		return (false);
	}
	return (true);
}