#include "xleaks.h"

void active_rss_clear(void)
{
	if (xleak_trace.list == NULL)
		return ;

	t_active_rss *t1 = xleak_trace.list;
	t_active_rss *t2 = NULL;

	while (t1)
	{
		t2 = t1;
		t1 = t1->next;
		if (t2->backtrace)
			free(t2->backtrace);
		free(t2);
	}
}
