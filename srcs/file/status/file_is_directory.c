#include <sys/stat.h>
#include <stdbool.h>

bool file_is_directory(const char *filename)
{
	if (!filename || !*filename)
		return (false);

	struct stat sb = {0};
	if (stat(filename, &sb) != 0) {
		return (false);
	}
	
	return (S_IFDIR == (S_IFDIR & sb.st_mode));
}