#include "../incs/hexdump.h"
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void print_usage(void) {
    fprintf(stderr, "Usage: ./hdump [OPTIONS] FILE\n\n");
    fprintf(stderr, "Description:\n");
    fprintf(stderr, "  Display the contents of a file in hexadecimal format.\n\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  --size=SIZE\t\tMaximum number of bytes to read from the file (default: unlimited).\n");
    fprintf(stderr, "  --start=OFFSET\tStarting byte offset to read from (default: 0).\n");
    fprintf(stderr, "  --end=OFFSET\t\tEnding byte offset (default: end of file).\n");
    fprintf(stderr, "  --raw\t\t\tOutput raw bytes in hexadecimal format, without formatting.\n\n");
    fprintf(stderr, "Arguments:\n");
    fprintf(stderr, "  FILE\t\t\tThe path to the file to be read.\n\n");
}

char	*str_to_uint(char *str, int64_t *result)
{
	long		tmp;

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

static const char *get_next_argument(int *ac, char ***av)
{
	if (*ac) {
		--(*ac);
		return (*++*av);
	}
	return (NULL);
}

int main(int ac, char *av[])
{
	t_dump_params params;
	char	*ptr;

	if (ac < 2) {
		print_usage();
		return (EXIT_FAILURE);
	}
	memset(&params, 0, sizeof(params));
	while ((ptr = (char *)get_next_argument(&ac, &av)) != NULL) {
		if (strncmp(ptr, "--size=", 7) == 0) {
			if (!str_to_uint(ptr + 7, &params.max_size))
				return (
					fprintf(stderr, "incorrect format: --size\n"),
					print_usage(),
					EXIT_FAILURE);
		} else if (strncmp(ptr, "--start=", 8) == 0) {
			if (!str_to_uint(ptr + 8, &params.start_offset))
				return (
					fprintf(stderr, "incorrect format: --start\n"),
					print_usage(),
					EXIT_FAILURE);
		} else if (strncmp(ptr, "--end=", 6) == 0) {
			if (!str_to_uint(ptr + 6, &params.end_offset))
				return (
					fprintf(stderr, "incorrect format: --end\n"),
					print_usage(),
					EXIT_FAILURE);
		} else if (strncmp(ptr, "--raw", 5) == 0) {
			params.mode = DUMP_RAW;
		} else {
			if (params.filename != NULL) {
				return (print_usage(), EXIT_FAILURE);
			}
			params.filename = ptr;
		}
	}
	return (hexdump(&params));
}