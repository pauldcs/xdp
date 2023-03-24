#include <sys/stat.h>
#include <stdbool.h>

int file_exists (const char *filename)
{
  struct stat sb;
  return (stat(filename, &sb) == 0);
}