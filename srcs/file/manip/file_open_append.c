#include "log.h"
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

bool file_open_append(const char *filename, int *fd)
{
	*fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (*fd != -1)
		return (true);
	
	__log__(error, "%s: %s", filename, ERROR_MSG);
	return (false);
}