#include "hexdump.h"
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

bool open_hexable_file(t_dump_params *params)
{
	struct stat st;
		
	if (stat(params->file.filename, &st) == -1)
		return (report_error("%s: %s\n",
				params->file.filename, strerror(errno)),
			false);
	
	if (S_ISDIR(st.st_mode))
		return (report_error("%s: %s\n",
				params->file.filename, "is a directory"),
			false);

	if (!S_ISREG(st.st_mode))
		return (report_error("%s: %s\n",
				params->file.filename, "Is not a regular file"),
			false);

	params->file.fd = open(params->file.filename, O_RDONLY);
	if (params->file.fd == -1)
		return (report_error("%s: %s\n",
				params->file.filename, strerror(errno)),
			false);
	
	params->file.file_size = st.st_size;
	return (true);
}