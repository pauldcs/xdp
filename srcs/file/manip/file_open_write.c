#include "debug/logging.h"
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

bool file_open_write(const char *filename, int *fd)
{
	*fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (*fd == -1)
	{
		FATAL_ERROR("%s: %s", filename, strerror(errno));
		return (false);
	}
	return (true);
}