#include "hexdump.h"
#include "libstringf.h"
#include "reader.h"
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

static unsigned char	*read_data_from_stdin(t_dump_params *params)
{
	unsigned char	*map;
	t_reader        r;
	int             ret;

	r.fd = 0;
	r.save.buf = NULL;
	r.save.size = 0;
	r.max_size = params->max_size;
	ret = reader(&map, &r, "");
	
	if (ret == -1)
		return (NULL);
	params->actual_size = ret;
	reader_destroy(&r);
	return (map);
}

bool prepare_params_struct(t_dump_params *params)
{
    struct stat st;

    if (!params->filename) {
		params->is_stdin = true;
        params->map = read_data_from_stdin(params);
		params->map_type = MALLOC;
        if (params->map == NULL)
            return (report_error(
					"Failed to read data from stdin\n"),
				false);

    } else {

		if (stat(params->filename, &st) == -1)
			return (report_error("%s: %s\n",
					params->filename, strerror(errno)),
				false);
	
		if (S_ISDIR(st.st_mode))
			return (report_error("%s: %s\n",
					params->filename, "is a directory"),
				false);

		if (!S_ISREG(st.st_mode))
			return (report_error("%s: %s\n",
					params->filename, "Is not a regular file"),
				false);

		params->fd = open(params->filename, O_RDONLY);
		if (params->fd == -1)
			return (report_error("%s: %s\n",
					params->filename, strerror(errno)),
				false);
		
		params->actual_size = st.st_size;
	}

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
        if (params->max_size > params->end_offset - params->start_offset)
            return (report_error(
					"'--size' exceeds the range '--start' to '--end'\n"),
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