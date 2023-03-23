#include "infile.h"
#include "debug/logging.h"
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void infile_close(t_infile *file)
{
	if (file->open)
	{
		__log(Debug, "closing fd %d", file->fd);
		close(file->fd);
		file->open = false;
	}
}

bool infile_open(t_infile *file)
{
	file->fd = open(file->name, O_RDONLY);
	if (file->fd == -1)
	{
		FATAL_ERROR("%s: %s", file->name, strerror(errno));
		return (false);
	}
	file->open = true;
	return (true);
}