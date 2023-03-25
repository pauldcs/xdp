#include "debug/logging.h"
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

bool file_open_read(const char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		FATAL_ERROR("%s: %s", filename, strerror(errno));
		return (false);
	}
	return (true);
}