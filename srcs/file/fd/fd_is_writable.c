#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>


bool fd_is_writable(int fd)
{
    if (fd < 0)
        return (false);

    int ret = fcntl(fd, F_GETFL);
    return (ret != -1 && (ret & O_ACCMODE) != O_RDONLY);
}