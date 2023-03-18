#include "hexdump.h"
#include "libstringf.h"

void debug_params(t_dump_params *params)
{
	putstr("<--- DEBUG --->\n");
	putstr("   - mode            %s\n", (params->mode == DUMP_RAW ? "raw" : "classic"));
	putstr("   - stdin           %s\n", (params->is_stdin ? "yes" : "no"));
	putstr("   - aligned_offset  %d\n", params->aligned_offset);
	putstr("   - map_type        %s\n", (params->map_type == MMAP ? "mmap" : "malloc"));
	putstr("   - size            %d\n", params->actual_size);
	putstr("   - map_size        %d\n", params->map_size);
	putstr("   - max_size        %d\n", params->max_size);
	putstr("   - start_offset    %d\n", params->start_offset);
	putstr("   - end_offset      %d\n\n", params->end_offset);
}
