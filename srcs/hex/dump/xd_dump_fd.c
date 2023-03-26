#include "hex.h"
#include "log.h"
#include "xmem.h"
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 32768

bool	xd_dump_fd(int fd, size_t n, size_t offset)
{
	cut8    *ptr = NULL;
	size_t  buffer_size;
	bool    inf;

	if (n == 0) {
		buffer_size = 32768;
		inf = true;
	} else {
		buffer_size = n;
		inf = false;
	}

	if (!xmem_alloc((void **)&ptr, buffer_size))
		return (false);

	ssize_t ret = read(fd, (ptr_t)ptr, offset);
	if (ret < (ssize_t)offset) {
		xmem_free(&ptr);
		return (false);
	}
	
	while (true)
	{
		if (!inf && !n)
			break ;
		
		ret = read(fd, (ptr_t)ptr, buffer_size);
		if (ret == -1) {
			log_message(fatal, "failed to read from fd");
			xmem_free(&ptr);
			return (false);
		}
		if (ret == 0)
			break ;
		n -= (ret > (ssize_t)n ? n : ret);
		xd_dump_lines(ptr, ret, offset);
		offset += ret;
	}
	xmem_free(&ptr);
	return (true);
}