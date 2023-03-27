#include <sys/socket.h>
#include <stdbool.h>

bool fd_is_socket(int fd)
{
    if (fd < 0)
        return (false);

    int type;
    socklen_t len = sizeof(type);
    return (getsockopt(fd, SOL_SOCKET, SO_TYPE, &type, &len) != -1);
}