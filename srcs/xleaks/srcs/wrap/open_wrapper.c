#include "xleaks.h"
#include <unistd.h>
#include <fcntl.h>

int open_wrapper(const char *path, int oflag, mode_t mode, const char *file, size_t line)
{
	int fd = open(path, oflag, mode);
	if (fd == -1)
		return (-1);
	
	t_active_rss *rss = active_rss_new_fd(
		fd,
		file,
		line);
	
	if (rss == NULL) {
		close(fd);
		return (-1);
	}

	active_rss_add(rss);
	return (fd);
}