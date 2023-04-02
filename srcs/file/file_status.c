#include "log.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

bool file_exists(const char *filename)
{
	if (filename && *filename)
	{
		if (access(filename, F_OK) == 0)
			return (true);

		__log__(error, "'%s': %s", filename, ERROR_MSG);
    	return (false);
	}
	__log__(error, "'%s': No input file", filename);
	return (false);
}

bool file_is_directory(const char *filename)
{
	if (!file_exists(filename))
		return (false);

	struct stat sb = {0};
	if (stat(filename, &sb) == 0
		&& (S_IFDIR & sb.st_mode) == S_IFDIR) {
		return (true);
	}
	
	__log__(error, "'%s': %s", filename, ERROR_MSG);
	return (false);
}

bool file_is_regular(const char *filename)
{
	if (!file_exists(filename))
		return (false);

	struct stat sb = {0};
	if (stat(filename, &sb) == 0
		&& (S_IFREG & sb.st_mode) == S_IFREG) {
		return (true);
	}
	
	__log__(error, "'%s': %s", filename, ERROR_MSG);
	return ((S_IFREG & sb.st_mode) == S_IFREG);
}

bool file_get_size(const char *filename, size_t *size)
{
	struct stat sb = {0};

	if (!file_exists(filename))
		return (false);
	
	if (stat(filename, &sb) == 0) {
		*size = sb.st_size;
		return (true);
	}

	__log__(error, "'%s': %s", filename, ERROR_MSG);
	return (false);
}

bool fd_is_block_device(int fd)
{
    if (fd < 0) 
        return (false);

    struct stat st;
    if (fstat(fd, &st) == -1)
        return (false);

    return (S_ISBLK(st.st_mode));
}

bool fd_is_character_device(int fd)
{
    if (fd < 0)
        return (false);

    struct stat st;
    if (fstat(fd, &st) == -1)
        return (false);

    return (S_ISCHR(st.st_mode));
}

bool is_directory(int fd)
{
    if (fd < 0)
        return (false);

    struct stat st;
    if (fstat(fd, &st) == -1)
        return (false);

    return (S_ISDIR(st.st_mode));
}

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

bool fd_is_readable(int fd)
{
    if (fd < 0)
        return (false);

    int ret = fcntl(fd, F_GETFL);
    return (ret != -1 && (ret & O_ACCMODE) != O_WRONLY);
}

bool fd_is_regular(int fd)
{
    if (fd < 0)
        return (false);
    
    struct stat st;
    if (fstat(fd, &st) == -1)
        return (false);

    return (S_ISREG(st.st_mode));
}

bool fd_is_socket(int fd)
{
    if (fd < 0)
        return (false);

    int type;
    socklen_t len = sizeof(type);
    return (getsockopt(fd, SOL_SOCKET, SO_TYPE, &type, &len) != -1);
}

bool fd_is_valid(int fd)
{
    if (fd < 0)
        return (false);

	errno = 0;
    int ret = fcntl(fd, F_GETFD);
    return (ret != -1 || errno != EBADF);
}

bool fd_is_writable(int fd)
{
    if (fd < 0)
        return (false);

    int ret = fcntl(fd, F_GETFL);
    return (ret != -1 && (ret & O_ACCMODE) != O_RDONLY);
}