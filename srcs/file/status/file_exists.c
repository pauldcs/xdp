#include <sys/stat.h>
#include <stdbool.h>

bool file_exists(const char *filename)
{
  if (!filename || !*filename)
		return (-1);

  struct stat sb;
  return (stat(filename, &sb) == 0);
}