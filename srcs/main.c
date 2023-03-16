#include "hexdump.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char *av[])
{
	int ret;

	if (ac < 2) {
		write(
			STDERR_FILENO,
			"Error: Usage\n",
			14);
		return (EXIT_FAILURE);
	}
	while (--ac)
	{
		++av;
		if (!strcmp(*av, "-r")
			|| !strcmp(*av, "--raw")) {
			if (--ac)
				ret = hexdump(*++av, DUMP_RAW);
			else {
				write(
					STDERR_FILENO,
					"Error: Missing argument\n",
					25);
				return(EXIT_FAILURE);
			}
		}
		else
			ret = hexdump(*av, CLASSIC);
	}
	return (ret);
}