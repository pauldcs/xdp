#include "xleaks.h"

bool active_rss_delete(void *scent, t_rss_type type)
{
	t_active_rss *active = xleak_trace.list;
	t_active_rss *prev = NULL;

	if (active == NULL)
		return (NULL);
	
	switch (type) {
	case MEMORY:
		while (active) {
			if (scent == active->rss.block.ptr) {
				xleak_trace.in_use.n_blocks--;
				xleak_trace.in_use.n_bytes -= active->rss.block.size;
				xleak_trace.n_frees++;
				goto hell;
			}
			prev = active;
			active = active->next;
		}
		return (false);
	case FILDES:
		while (active) {
			if ((size_t)scent == (size_t)active->rss.fd) {
				xleak_trace.in_use.n_fds--;
				goto hell;
			}
			prev = active;
			active = active->next;
		}
		return (false);
	}
	return (false);

hell:
	if (!prev)
		xleak_trace.list = active->next;
	else
		prev->next = active->next;
	free(active);
	return (true);
}