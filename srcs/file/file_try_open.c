#include "hdump.h"
#include "logging.h"
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

/* Performs basic validation to ensure it is a regular file.
 * If successful, sets the file descriptor and file size in the parameters.
 */
ssize_t file_try_open(const char *filename, int *fd)
{
	struct stat st;
	ssize_t     ret;
		
	if (stat(filename, &st) == -1) {
		FATAL_ERROR("%s: %s\n", filename, strerror(errno));
		return (-1);
	}
	
	if (S_ISDIR(st.st_mode)) {
		FATAL_ERROR("%s: %s\n", filename, "is a directory");
		return (-1);
	}

	if (!S_ISREG(st.st_mode)) {
		FATAL_ERROR("%s: %s\n", filename, "Is not a regular file");
		return (-1);
	}
	
	if ((*fd = open(filename, O_RDONLY)) == -1) {
		FATAL_ERROR("%s: %s\n", filename, strerror(errno));
		return (-1);
	} else {
		ret = st.st_size;
	}

	LOG(DEBUG,
		"opened file: %s (size: %db)",
			filename,
			ret
	);
	return (ret);
}