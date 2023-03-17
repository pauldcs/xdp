#include "hexdump.h"
#include "libstringf.h"
#include "reader.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

static unsigned char	*read_data_from_stdin(void)
{
	unsigned char	*line;
	t_reader        r;
	int             ret;

	r.fd = 0;
	r.save.buf = NULL;
	r.save.size = 0;
	ret = reader(&line, &r, "");
	if (ret == -1)
		return (NULL);
	reader_destroy(&r);
	return (line);
}

bool handle_parameters(t_dump_params *params)
{
	struct stat	st;
	
	if (params->is_stdin) {
		if ((params->map = read_data_from_stdin()) == NULL)
			return (false);
		params->actual_size = strlen(params->map);
	} else {
		if (stat(params->filename, &st) == -1)
			return (perror(params->filename), false);
		params->actual_size = st.st_size;
		if (S_ISDIR(st.st_mode))
			return (fputstr(2, "%s: Is a directory\n", params->filename),
				false);
		if (!S_ISREG(st.st_mode))
			return (fputstr(2, "%s: Is not a regular file\n", params->filename),
				false);
		if ((params->fd = open(params->filename, O_RDONLY)) == -1)
			return (perror(params->filename), false);
	}

	if (!params->end_offset)
			params->end_offset = params->actual_size;

	if (params->start_offset || params->end_offset){
		assert(params->start_offset <= params->end_offset
			&& "Start offset comes after the end offset ?");
		assert(params->start_offset <= params->actual_size
			&& "Start offset comes after EOF");
		assert(params->end_offset <= params->actual_size
			&& "End offset comes after EOF");
	}

	if (params->max_size) {
		assert(params->max_size < params->actual_size
			&& "Number of bytes to print exceeds the actual size");
		assert(params->max_size < (params->end_offset - params->start_offset)
			&& "Trying to dump more bytes than available in the range start - end");	
	} else {
		params->max_size = (params->end_offset - params->start_offset);
	}
	return (true);
}