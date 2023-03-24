#include <sys/stat.h>
#include <stdbool.h>

bool file_is_regular(const char *str)
{
	if (!str || !*str)
		return (false);

	struct stat sb = {0};
	if (stat(str, &sb) != 0) {
		return (false);
	}
	
	return ((S_IFREG & sb.st_mode) == S_IFREG);
}