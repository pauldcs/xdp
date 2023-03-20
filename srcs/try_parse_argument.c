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

bool try_parse_argument(const char *argument, t_dump_params *params, int *ac, char ***av)
{
    char *arg;

    if (!strncmp(argument, "--size", 6)) {
        if (*(argument + 6) == '=') {
            if (!str_to_uint(
                    argument + 7,
                    &params->file.range_size))
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);
        } else if ((arg = get_next_argument(ac, av)) != NULL) {
            if (!str_to_uint(
                arg,
                &params->file.range_size))
                return (report_error("'%s': %s\n", argument, "Invalid format"),
                    false);
        } else 
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);

    } else if (!strncmp(argument, "--start", 7)) {
        if (*(argument + 7) == '=') {
            if (!str_to_uint(
                    argument + 8,
                    &params->file.start_offset))
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);
        } else if ((arg = get_next_argument(ac, av)) != NULL) {
            if (!str_to_uint(
                arg,
                &params->file.start_offset))
                return (report_error("'%s': %s\n", argument, "Invalid format"),
                    false);
        } else 
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);

    } else if (!strcmp(argument, "-")) {
        params->is_stdin = true;

    } else if (!strcmp(argument, "-r")
           || !strcmp(argument, "--raw")) {
        params->mode = DUMP_RAW;

    } else if (!strncmp(argument, "--string", 8)) {
        params->mode = DUMP_STRINGS;
        if (*(argument + 8) == '=') {
            if (!str_to_uint(
                    argument + 9,
                    &params->string_size))
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);
        } else if ((arg = get_next_argument(ac, av)) != NULL) {
            if (!str_to_uint(
                arg,
                &params->string_size))
                return (report_error("'%s': %s\n", argument, "Invalid format"),
                    false);
        } else 
            return (report_error("'%s': %s\n", argument, "Invalid format"),
                false);

    } else if (!strcmp(argument, "-c")
             ||!strcmp(argument, "--color")) {
        params->colored_output = true;

    } else if (!strcmp(argument, "-h")
            || !strcmp(argument, "--help")) {
        __usage();
        exit (0);

    } else if (!params->file.filename) {
        params->file.filename = argument;
    } else {
        return (report_error("'%s': %s\n", argument, "Unrecognized argument"),
                false);
    }
    return (true);
}