#include "hexdump.h"
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

bool safe_open(t_dump_params *params)
{
	struct stat st;
		
	if (stat(params->filename, &st) == -1)
		return (report_error("%s: %s\n",
				params->filename, strerror(errno)),
			false);
	
	if (S_ISDIR(st.st_mode))
		return (report_error("%s: %s\n",
				params->filename, "is a directory"),
			false);

	if (!S_ISREG(st.st_mode))
		return (report_error("%s: %s\n",
				params->filename, "Is not a regular file"),
			false);

	params->fd = open(params->filename, O_RDONLY);
	if (params->fd == -1)
		return (report_error("%s: %s\n",
				params->filename, strerror(errno)),
			false);
	
	params->actual_size = st.st_size;
	return (true);
}