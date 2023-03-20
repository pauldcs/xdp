#include "hexdump.h"
#include "logging.h"
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

/* Performs basic validation to ensure it is a regular file.
 * If successful, sets the file descriptor and file size in the parameters.
 */
bool open_hexable_file(t_dump_params *params)
{
	struct stat st;
		
	if (stat(params->file.filename, &st) == -1) {
		FATAL_ERROR("%s: %s\n", params->file.filename, strerror(errno));
		return (false);
	}
	
	if (S_ISDIR(st.st_mode)) {
		FATAL_ERROR("%s: %s\n", params->file.filename, "is a directory");
		return (false);
	}

	if (!S_ISREG(st.st_mode)) {
		FATAL_ERROR("%s: %s\n", params->file.filename, "Is not a regular file");
		return (false);
	}

	params->file.fd = open(params->file.filename, O_RDONLY);
	
	if (params->file.fd == -1) {
		FATAL_ERROR("%s: %s\n", params->file.filename, strerror(errno));
		return (false);
	}
	
	params->file.file_size = st.st_size;
	LOG(DEBUG,
		"opened file: %s (size: %db)",
		params->file.filename,
		params->file.file_size
	);
	return (true);
}