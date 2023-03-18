#include "hexdump.h"
#include "libstringf.h"
#include "reader.h"
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

bool build_dump_structure(t_dump_params *params)
{
    if (!params->end_offset)
        params->end_offset = params->actual_size;

	if ((params->start_offset || params->end_offset)
		&& (params->start_offset == params->end_offset))
		return (report_error(
				"'--start' and '--end' are the same ?\n"),
			false);
		
	if (params->start_offset > params->actual_size)
        return (report_error(
				"'--start' is beyond EOF\n"),
			false);

    if (params->start_offset > params->end_offset)
        return (report_error(
				"'--start' is beyond '--end'\n"),
			false);

    if (params->end_offset > params->actual_size) 
        return (report_error(
				"'--end' is beyond EOF\n"),
			false);

    if (params->max_size) {
		if (params->end_offset && params->start_offset
			&& params->max_size > params->end_offset - params->start_offset)
            return (report_error(
					"'--size' exceeds the range '--start' to '--end'\n"),
				false);
		if (params->end_offset && !params->start_offset
			&& params->end_offset < params->max_size)
			return (report_error(
					"'--size' exceeds the size avaible before '--end'\n"),
				false);

        if (params->max_size > params->actual_size)
            return (report_error(
					"'--size' exceeds the actual size\n"),
				false);

    } else {
        params->max_size = params->end_offset - params->start_offset;
		if (!params->max_size)
			params->max_size = params->actual_size;
    }

	if (!params->is_stdin) {
		if (params->max_size < params->actual_size)
			params->map_type = MALLOC;
		else
			params->map_type = MMAP;
	}
    return true;
}