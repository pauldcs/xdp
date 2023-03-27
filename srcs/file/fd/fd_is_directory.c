#include <sys/stat.h>
#include <stdbool.h>

bool is_directory(int fd)
{
    if (fd < 0)
        return (false);

    struct stat st;
    if (fstat(fd, &st) == -1)
        return (false);

    return (S_ISDIR(st.st_mode));
}