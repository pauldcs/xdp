#include "hexdump.h"
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
	int ret;

	if (ac < 2) {
		write(STDERR_FILENO, "Error: Usage\n", 14);
		return (EXIT_FAILURE);
	}
	while (--ac)
		ret = hexdump(*++av);
	return (ret);
}