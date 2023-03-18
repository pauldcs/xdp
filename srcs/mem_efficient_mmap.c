#include "libstringf.h"
#include "hexdump.h"
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

bool mem_efficient_mmap(t_dump_params *params)
{
	params->aligned_offset = params->start_offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
	params->start_offset = (params->start_offset - params->aligned_offset);
	params->map_size = params->max_size + params->start_offset;

	params->map = mmap(
			NULL,
			params->map_size,
	 		PROT_READ | PROT_WRITE,
	 		MAP_PRIVATE | MAP_FILE,
	 		params->fd,
			params->aligned_offset);
	
	if (params->map == MAP_FAILED)
		return (
			report_error("mmap: %s\n", strerror(errno)),
			false);

	return (true);
}