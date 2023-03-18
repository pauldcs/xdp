#include "hexdump.h"
#include "libstringf.h"
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

static const char	*str_to_uint(const char *str, int64_t *result)
{
	long tmp;

	tmp = 0;
    if (*str == '0' && *(str + 1) == 'x') {
        char *endptr;
        tmp = strtol(str, &endptr, 16);
        str = endptr;
        if (errno == ERANGE
            || tmp > INT_MAX
            || *str)
        return NULL;
    } else {
        while (*str >= '0' && *str <= '9')
        {
            tmp *= 10;
            tmp += *(str++) & 0xCF;
            if (tmp > INT_MAX)
                return (NULL);
        }
    }
	*result = tmp;
	if (*str)
		return (NULL);
	return (str);
}

bool parse_argument(const char *argument, t_dump_params *params)
{
    if (!strncmp(argument, "--size=", 7)) {
        if (!str_to_uint(argument + 7, &params->max_size))
            return (report_error(
                    "'%s': %s\n", argument, "Invalid format"),
                false);
    } else if (!strncmp(argument, "--start=", 8)) {
        if (!str_to_uint(argument + 8, &params->start_offset))
            return (report_error(
                    "'%s': %s\n", argument, "Invalid format"),
                false);
    } else if (!strncmp(argument, "--end=", 6)) {
        if (!str_to_uint(argument + 6, &params->end_offset))
            return (report_error(
                    "'%s': %s\n", argument, "Invalid format"),
                false);
    } else if (!strcmp(argument, "--raw"))
        params->mode = DUMP_RAW;
    else if (!strcmp(argument, "--stdin"))
        params->is_stdin = true;
    else if (!params->filename)
        params->filename = argument;
    return true;
}