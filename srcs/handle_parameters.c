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
	ret = reader(&map, &r, "");
	
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
            report_error("Error: Failed to read data from stdin\n");
            return false;
        }
        params->actual_size = strlen(params->map);

    } else {
		if (params->filename == NULL) {
			report_error("Error: No input file\n");
			return false;
		}

		if (stat(params->filename, &st) == -1) {
			report_error("%s: %s\n", params->filename, strerror(errno));
			return false;
		}

		if (S_ISDIR(st.st_mode)) {
			report_error("%s: Is a directory\n", params->filename);
			return false;
		}

		if (!S_ISREG(st.st_mode)) {
			report_error("%s: Is not a regular file\n", params->filename);
			return false;
		}

		params->fd = open(params->filename, O_RDONLY);
		if (params->fd == -1) {
			report_error("%s: %s\n", params->filename, strerror(errno));
			return false;
		}
		params->actual_size = st.st_size;
	}

    if (params->end_offset == 0) {
        params->end_offset = params->actual_size;
    }

	if (params->start_offset > params->actual_size) {
        report_error("'--start' is beyond EOF\n");
        return false;
    }

    if (params->start_offset > params->end_offset) {
        report_error("'--start' is beyond '--end'\n");
        return false;
    }

    if (params->end_offset > params->actual_size) {
        report_error("'--end' is beyond EOF\n");
        return false;
    }

    if (params->max_size) {
        if (params->max_size > params->end_offset - params->start_offset) {
            report_error("--size' exceeds the range '--start' to '--end'\n");
            return false;
        }

        if (params->max_size > params->actual_size) {
            report_error("'--size' exceeds the actual size\n");
            return false;
        }
    } else {
        params->max_size = params->end_offset - params->start_offset;
		if (!params->max_size)
			params->max_size = params->actual_size;
    }
    return true;
}