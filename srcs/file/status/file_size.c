#include <sys/stat.h>
#include <stdbool.h>
#include <stdint.h>

uint64_t file_size(const char *str)
{
	if (!str || !*str)
		return (-1);
	
	struct stat sb = {0};
	if (stat(str, &sb) != 0) {
		return (-1);
	}
	return ((uint64_t)sb.st_size);
}