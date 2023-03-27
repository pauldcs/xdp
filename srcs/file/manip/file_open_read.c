#include "log.h"
#include "xleaks.h"
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

bool file_open_read(const char *filename, int *fd)
{
	*fd = __xopen__(filename, O_RDONLY, 0666);
	if (*fd != -1)
		return (true);
	
	__log__(error, "%s: %s", filename, ERROR_MSG);
	return (false);
}