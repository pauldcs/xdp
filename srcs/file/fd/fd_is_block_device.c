#include <sys/stat.h>
#include <stdbool.h>

bool fd_is_block_device(int fd)
{
    if (fd < 0)
        return (false);

    struct stat st;
    if (fstat(fd, &st) == -1)
        return (false);

    return (S_ISBLK(st.st_mode));
}