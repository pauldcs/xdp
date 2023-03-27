#include "xleaks.h"
#include <unistd.h>
#include <fcntl.h>

int close_wrapper(int fildes, const char *file, size_t line)
{
	(void)file;
	(void)line;
	active_rss_delete(&fildes, FILDES);
	return (close(fildes));
}