#include "file.h"
#include "log.h"
#include <string.h>

bool file_init(const char *filename, t_file *file)
{
	memset(file, 0x00, sizeof(t_file));

	if (!file_exists(filename)
		|| !file_get_size(filename, &file->size))
		return (false);

	file->name = filename;
	return (true);
}