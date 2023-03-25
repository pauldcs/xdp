#include "file.h"
#include "log.h"
#include <sys/stat.h>
#include <stdbool.h>

bool file_is_directory(const char *filename)
{
	if (!file_exists(filename))
		return (false);

	struct stat sb = {0};
	if (stat(filename, &sb) == 0
		&& (S_IFDIR & sb.st_mode) == S_IFDIR) {
		return (true);
	}
	
	log_message(error, "'%s': %s", filename, ERROR_MSG);
	return (false);
}