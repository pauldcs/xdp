#include "log.h"
#include "file.h"
#include <sys/stat.h>
#include <stdbool.h>

bool file_is_regular(const char *filename)
{
	if (!file_exists(filename))
		return (false);

	struct stat sb = {0};
	if (stat(filename, &sb) == 0
		&& (S_IFREG & sb.st_mode) == S_IFREG) {
		return (true);
	}
	
	log_message(error, "'%s': %s", filename, ERROR_MSG);
	return ((S_IFREG & sb.st_mode) == S_IFREG);
}