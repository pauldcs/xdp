#include "xleaks.h"

void active_rss_clear(void)
{
	if (xleak_trace.list == NULL)
		return ;

	t_active_rss *tmp_1 = xleak_trace.list;
	t_active_rss *tmp_2 = NULL;

	while (tmp_1)
	{
		tmp_2 = tmp_1;
		tmp_1 = tmp_1->next;
		free(tmp_2);
	}
}
