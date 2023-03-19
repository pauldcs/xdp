#include "libstringf.h"
#include "hexdump.h"
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

bool file_partial_mmap(t_dump_params *params)
{
	params->aligned_offset = params->start_offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
	params->start_offset = (params->start_offset - params->aligned_offset);
	params->capacity = params->range_size + params->start_offset;

	params->data = mmap(
			NULL,
			params->capacity,
	 		PROT_READ | PROT_WRITE,
	 		MAP_PRIVATE | MAP_FILE,
	 		params->fd,
			params->aligned_offset);
	
	if (params->data == MAP_FAILED)
		return (
			report_error("mmap: %s\n", strerror(errno)),
			false);

	return (true);
}