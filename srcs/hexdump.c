#include "xtypes.h"
#include "xleaks.h"
#include "file.h"
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

# define RDSIZE 2048

bool hexdump(int fd, size_t max_size, size_t start_offset)
{
	int    ret;
	cut8   buffer[RDSIZE];
	size_t offset = 0;

	(void)start_offset;

	if (read(fd, NULL, 0) == -1)
		goto prison;

	while (true)
	{
		if (max_size && offset >= max_size)
			break;
		
		ret = read(fd, (ptr_t)buffer, RDSIZE);
		switch (ret)
		{
			case  0:
				goto beach;
			case -1:
				goto prison;
			default:
				write (1, buffer, ret);
		}
		offset += ret;
	}

beach:
	__xclose__(fd);
	return (true);

prison:
	__xclose__(fd);
	return (false);

}