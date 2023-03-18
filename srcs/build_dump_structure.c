#include "hexdump.h"
#include <stdbool.h>

bool build_dump_structure(t_dump_params *params)
{
	if (!params->end_offset)
	{
		if (params->range_size)
			params->end_offset = params->range_size;
		else
			params->end_offset = params->file_size;
	}
	if (params->start_offset > params->end_offset)
		return (report_error(
			"Invalid range"
		), false);

	if (params->range_size > params->end_offset - params->start_offset)
		return (report_error(
			"Invalid range"
		), false);
	
	if (!params->range_size)
		params->range_size = params->end_offset - params->start_offset;

	if (params->start_offset)
		params->end_offset = params->start_offset + params->range_size;

	if (!params->start_offset)
		params->start_offset = params->end_offset - params->range_size;

	params->data += params->start_offset;
	return (true);
}