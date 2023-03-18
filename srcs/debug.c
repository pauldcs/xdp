#include "hexdump.h"
#include "libstringf.h"

void debug_params(t_dump_params *params)
{
	putstr("\n<--- DEBUG --->\n");
	putstr("   - file_size       %d\n",   params->file_size);
	putstr("   - is_mapped       %s\n",  (params->is_mapped ? "true" : "false"));
	putstr("   - aligned_offset  %d\n",   params->aligned_offset);
	putstr("   - capacity        %d\n",   params->capacity);
	putstr("   - range_size      %d\n",   params->range_size);
	putstr("   - start_offset    %d\n",   params->start_offset);
	putstr("   - end_offset      %d\n\n", params->end_offset);
}
