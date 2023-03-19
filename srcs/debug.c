#include "hexdump.h"
#include "logging.h"
#include "libstringf.h"

void debug_params(t_dump_params *params)
{
	(void)params;

	LOG(INFO, "file_size: %d",   params->file_size);
	LOG(INFO, "is_mapped: %s",  (params->is_mapped ? "true" : "false"));
	LOG(INFO, "aligned_offset: %d",   params->aligned_offset);
	LOG(INFO, "capacity: %d",   params->capacity);
	LOG(INFO, "range_size: %d",   params->range_size);
	LOG(INFO, "start_offset: %d",   params->start_offset);
}
