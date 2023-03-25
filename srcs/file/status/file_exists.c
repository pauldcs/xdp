#include "log.h"
#include <unistd.h>
#include <stdbool.h>

bool file_exists(const char *filename)
{
	if (filename
		&& *filename
   		&& access(filename, F_OK) == 0) {
    	return (true);
	}

	log_message(error, "File does not exist");
	return (false);
}