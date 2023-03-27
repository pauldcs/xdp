#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

bool fd_is_pipe (int fd)
{
	if (fd < 0)
        return (false);

	errno = 0;
	return (
		(lseek (fd, 0L, SEEK_CUR) < 0)
		&& (errno == ESPIPE)
	);
}