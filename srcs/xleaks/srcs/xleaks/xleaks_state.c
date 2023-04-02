#include "xleaks.h"	
#include <stdio.h>
#include <unistd.h>

void xleaks_state(void)
{
	t_active_rss *tmp = xleak_trace.list;

	if (xleak_trace.list == NULL)
		return;

	write(1,"\n",1);
	while (tmp)
	{
		active_rss_print(tmp);
		tmp = tmp->next;
	}
}