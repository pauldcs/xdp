#include <fcntl.h>

int sh_validfd (int fd)
{
	return (fcntl (fd, F_GETFD, 0) >= 0);
}
