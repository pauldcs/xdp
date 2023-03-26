#include "xmem.h"
#include <stdlib.h>

void xmem_trace_destroy(void)
{
	if (mem_trace.list)
	{
		t_xmem_alloc *tmp_1 = mem_trace.list;
		t_xmem_alloc *tmp_2 = NULL;

		while (tmp_1)
		{
			tmp_2 = tmp_1;
			tmp_1 = tmp_1->next;
			free(tmp_2);
		}
	}
}