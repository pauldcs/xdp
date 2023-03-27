#include "log.h"
#include "file.h"
#include <sys/stat.h>
#include <stddef.h>
#include <stdbool.h>

bool file_get_size(const char *filename, size_t *size)
{
	struct stat sb = {0};

	if (!file_exists(filename))
		return (false);
	
	if (stat(filename, &sb) == 0) {
		*size = sb.st_size;
		return (true);
	}

	__log__(error, "'%s': %s", filename, ERROR_MSG);
	return (false);
}