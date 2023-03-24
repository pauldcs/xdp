#include <errno.h>
#include <unistd.h>

int fd_ispipe (int fd)
{
	errno = 0;
	return (
		(lseek (fd, 0L, SEEK_CUR) < 0)
		&& (errno == ESPIPE)
	);
}