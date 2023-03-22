#include "hdump.h"
#include "file/file.h"
#include "logging.h"
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

/* Performs basic validation to ensure it is a regular file.
 * If successful, sets the file descriptor and file size in the parameters.
 */
bool file_try_open(t_hd_file *file)
{
	struct stat st;
		
	if (stat(file->name, &st) == -1) {
		FATAL_ERROR("%s: %s\n", file->name, strerror(errno));
		return (false);
	}
	
	if (S_ISDIR(st.st_mode)) {
		FATAL_ERROR("%s: %s\n", file->name, "is a directory");
		return (false);
	}

	if (!S_ISREG(st.st_mode)) {
		FATAL_ERROR("%s: %s\n", file->name, "Is not a regular file");
		return (false);
	}
	
	if ((file->fd = open(file->name, O_RDONLY)) == -1) {
		FATAL_ERROR("%s: %s\n", file->name, strerror(errno));
		return (false);
	} else {
		file->size = st.st_size;
	}

	LOG(DEBUG,
		"opened file: %s (size: %db)",
			file->name, file->size
	);
	return (true);
}