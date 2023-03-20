#include "reader.h"

ssize_t read_from_fd(int fd, char **data)
{
	int  ret;
	t_reader r = {
		.fd = -1,
		.save.buf = NULL,
		.save.size = 0,
		.max_size = 0x10000
	};

	ret = reader(data, &r, "");
	reader_destroy(&r);
	
	return (ret);
}