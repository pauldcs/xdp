#include "xdp.h"
#include "infile.h"
#include "debug/logging.h"
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

/* Performs basic validation to ensure it is a regular file.
 * If successful, sets the file descriptor and file size in the parameters.
 */
bool infile_get_size(t_infile *file)
{
	struct stat st;
	
	if (!file->name) {
		FATAL_ERROR("Missing name");
		return (false);
	}
	
	if (stat(file->name, &st) == -1) {
		FATAL_ERROR("%s: %s", file->name, strerror(errno));
		return (false);
	}
	
	if (S_ISDIR(st.st_mode)) {
		FATAL_ERROR("%s: %s", file->name, "Is a directory");
		return (false);
	}

	if (!S_ISREG(st.st_mode)) {
		FATAL_ERROR("%s: %s", file->name, "Is not a regular file");
		return (false);
	}

	file->size = st.st_size;
	return (true);
}