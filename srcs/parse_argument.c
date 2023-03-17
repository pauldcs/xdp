#include "hexdump.h"
#include "libstringf.h"
#include <limits.h>
#include <string.h>
#include <stdbool.h>

static const char	*str_to_uint(const char *str, int64_t *result)
{
	long tmp;

	tmp = 0;
	while (*str >= '0' && *str <= '9')
	{
		tmp *= 10;
		tmp += *(str++) & 0xCF;
		if (tmp > INT_MAX)
			return (NULL);
	}
	*result = tmp;
	if (*str)
		return (NULL);
	return (str);
}

bool parse_argument(const char *argument, t_dump_params *params) {
    if (argument == NULL || params == NULL) {
        return (fputstr(2, "%s: Invalid format", argument), false);
    }
    if (strncmp(argument, "--size=", 7) == 0) {
        if (!str_to_uint(argument + 7, &params->max_size)) {
            return (fputstr(2, "%s: Invalid format", argument), false);
        }
    } else if (strncmp(argument, "--start=", 8) == 0) {
        if (!str_to_uint(argument + 8, &params->start_offset)) {
            return (fputstr(2, "%s: Invalid format", argument), false);
        }
    } else if (strncmp(argument, "--end=", 6) == 0) {
        if (!str_to_uint(argument + 6, &params->end_offset)) {
            return (fputstr(2, "%s: Invalid format", argument), false);
        }
    } else if (strcmp(argument, "--raw") == 0) {
        params->mode = DUMP_RAW;
    } else if (strcmp(argument, "--stdin") == 0) {
        params->is_stdin = true;
    } else {
        if (params->filename != NULL) {
            return (fputstr(2, "%s: Duplicate filename", argument), false);
        }
        params->filename = argument;
    }
    return true;
}