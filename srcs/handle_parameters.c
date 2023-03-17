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

static unsigned char	*read_data_from_stdin(void)
{
	unsigned char	*map;
	t_reader        r;
	int             ret;

	r.fd = 0;
	r.save.buf = NULL;
	r.save.size = 0;
	ret = reader(&map, &r, "\0");
	
	if (ret == -1)
		return (NULL);
	
	reader_destroy(&r);
	return (map);
}

bool handle_parameters(t_dump_params *params)
{
    struct stat st;

    if (params->is_stdin) {
        params->map = read_data_from_stdin();
        if (params->map == NULL) {
            fputstr(2, "Failed to read data from stdin\n");
            return false;
        }
        params->actual_size = strlen(params->map);
        return true;

    } else {
		if (params->filename == NULL) {
			fputstr(2, "No input file\n");
			return false;
		}

		if (stat(params->filename, &st) == -1) {
			fputstr(2, "%s: %s\n", params->filename, strerror(errno));
			return false;
		}

		if (S_ISDIR(st.st_mode)) {
			fputstr(2, "%s: Is a directory\n", params->filename);
			return false;
		}

		if (!S_ISREG(st.st_mode)) {
			fputstr(2, "%s: Is not a regular file\n", params->filename);
			return false;
		}

		params->fd = open(params->filename, O_RDONLY);
		if (params->fd == -1) {
			fputstr(2, "%s: %s\n", params->filename, strerror(errno));
			return false;
		}
		params->actual_size = st.st_size;
	}

    if (params->end_offset == 0) {
        params->end_offset = params->actual_size;
    }

    if (params->start_offset > params->end_offset) {
        fputstr(2, "Start offset comes after the end offset\n");
        return false;
    }

    if (params->start_offset > params->actual_size) {
        fputstr(2, "Start offset comes after EOF\n");
        return false;
    }

    if (params->end_offset > params->actual_size) {
        fputstr(2, "End offset comes after EOF\n");
        return false;
    }

    if (params->max_size > 0) {
        if (params->max_size > params->end_offset - params->start_offset) {
            fputstr(2, "Trying to dump more bytes than available in the range start - end\n");
            return false;
        }

        if (params->max_size > params->actual_size) {
            fputstr(2, "Number of bytes to print exceeds the actual size\n");
            return false;
        }
    } else {
        params->max_size = params->end_offset - params->start_offset;
    }
    return true;
}