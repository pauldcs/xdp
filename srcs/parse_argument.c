#include "hexdump.h"
#include "libstringf.h"
#include <limits.h>
#include <string.h>
#include <stdbool.h>

static char	*str_to_uint(char *str, int64_t *result)
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

bool parse_argument(char *argument, t_dump_params *params)
{
	if (!strncmp(argument, "--size=", 7)) {
		if (!str_to_uint(argument + 7, &params->max_size))
			return (fputstr(2, "incorrect format: --size\n"), display_usage(), false);
	} else if (!strncmp(argument, "--start=", 8)) {
		if (!str_to_uint(argument + 8, &params->start_offset))
		return (fputstr(2, "incorrect format: --start\n"), display_usage(), false);
	} else if (!strncmp(argument, "--end=", 6)) {
		if (!str_to_uint(argument + 6, &params->end_offset))
			return (fputstr(2, "incorrect format: --end\n"), display_usage(), false);
	} else if (!strncmp(argument, "--raw", 5)) {
		params->mode = DUMP_RAW;
	} else if (!strncmp(argument, "--stdin", 7)) {
		params->is_stdin = true;
	} else {
		if (params->filename != NULL) {
			return (display_usage(), false);
		}
		params->filename = argument;
	}
	return (true);
}