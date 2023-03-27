#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

bool fd_is_valid(int fd)
{
    if (fd < 0)
        return (false);

	errno = 0;
    int ret = fcntl(fd, F_GETFD);
    return (ret != -1 || errno != EBADF);
}
