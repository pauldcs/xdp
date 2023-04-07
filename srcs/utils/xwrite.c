#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

/* Forces to write the buffer fully if write() failes, 
 * it's ok if this ends up looping endlessly.
 */
ssize_t xwrite(int fd, const char *buf, size_t nbytes)
{
	int i;
	int n = nbytes;
	int ntry = 0;

	for (;;)
	{
		i = write(fd, buf, n);
		if (i > 0)
		{
			if ((n -= i) <= 0)
				return (nbytes);
			buf += i;
			ntry = 0;
	
		} else if (i == 0)
		{
			if (++ntry > 10)
				return (nbytes - n);
	
		} else if (errno != EINTR)
			return (-1);
	}
}
