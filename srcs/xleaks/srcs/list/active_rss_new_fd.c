#include "xleaks.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_active_rss *active_rss_new_fd(
	int        fd,
	const char *file,
	size_t     line)
{
	t_active_rss *rss = malloc(sizeof(t_active_rss));
	if (rss == NULL)
		return (NULL);

	bzero(rss, sizeof(t_active_rss));

	rss->owner  = getpid();
	rss->file   = file;
	rss->line   = line;
	rss->type   = FILDES;
	rss->rss.fd = fd;

	return (rss);
}