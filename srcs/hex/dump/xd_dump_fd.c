#include "hex.h"
#include "log.h"
#include "file.h"
#include "xmem.h"
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 32768

bool	xd_dump_fd(int fd, size_t n, size_t offset)
{
	cut8    *ptr = NULL;
	size_t  bufsize;
	ssize_t ret;
	bool    inf;

	if (n == 0) {
		inf = true;
		bufsize = 1 << 15;

	} else {
		inf = false;
		bufsize = n;
	}

	if (!xmem_alloc((ptr_t *)&ptr, bufsize))
		return (false);

	if (offset)
	{
		struct stat st;

		if (fstat(fd, &st) < 0)
        	goto prison;

		if (S_ISREG(st.st_mode))
		{
			ret = lseek(fd, offset, SEEK_CUR);
			if (ret == -1) 
				goto prison;
	
		} else {
			ssize_t ret;
			char 	buf[1024];
			size_t  i = offset;
	
			while (i)
			{
				size_t rd_size = i < 1024 ? i : 1024;
				ret = read(fd, buf, rd_size);
				if (ret == -1) 
					goto prison;
				i -= ret;
			}
		}
	}

	while (666)
	{
		if (!inf && !n) break ;
	
		ret = read(fd, (ptr_t)ptr, bufsize);
		switch (ret)
		{
			case -1: goto prison;
			case  0: goto beach;
		}
		xd_dump_lines(ptr, ret, offset);
		offset += ret;

		if (!inf)
			n -= ret;
	}

beach:
	xmem_free((ptr_t)ptr);	
	return (true);

prison:
	log_message(error, "xd_dump_fd() failed miserably");
	xmem_free((ptr_t)ptr);
	return (false);
}


