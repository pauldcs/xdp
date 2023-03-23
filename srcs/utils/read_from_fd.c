#include "infile/infile_reader.h"
#include <stddef.h>

ssize_t read_from_fd(int fd, char **data)
{
	int  ret;
	t_reader r = {
		.fd = -1,
		.save.buf = NULL,
		.save.size = 0,
		.max_size = 0x10000
	};

	ret = infile_reader(data, &r, "");
	infile_reader_destroy(&r);
	
	return (ret);
}