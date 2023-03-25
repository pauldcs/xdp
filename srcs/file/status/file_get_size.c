#include <sys/stat.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

bool file_get_size(const char *filename, size_t *size)
{
	if (!filename || !*filename)
		return (false);
	
	struct stat sb = {0};
	if (stat(filename, &sb) != 0)
		return (false);

	*size = sb.st_size;
	return (true);
}