#include "log.h"
#include <unistd.h>
#include <stdbool.h>

bool file_exists(const char *filename)
{
	if (filename && *filename)
	{
		if (access(filename, F_OK) == 0)
			return (true);

		__log__(error, "'%s': %s", filename, ERROR_MSG);
    	return (false);
	}
	__log__(error, "'%s': No input file", filename);
	return (false);
}