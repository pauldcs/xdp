#include "xmem.h"
#include "log.h"
#include "xtypes.h"
#include <stdlib.h>
#include <assert.h>

static void xmem_trace_remove(ptr_t ptr)
{
	assert (user_trace.list != NULL && "Trace list is null ?");

	t_xmem_alloc_node *tmp = user_trace.list;
	t_xmem_alloc_node *prev = NULL;

	while (tmp && tmp->block_ptr != ptr)
	{
		prev = tmp;
		tmp = tmp->next;
	}

	assert(tmp != NULL && "The block was not in the trace list");

	user_trace.cmalloc_n_frees += 1;
	user_trace.in_use.nbytes -= tmp->block_size;
	user_trace.in_use.nblocks -= 1;

	if (prev)
		prev->next = tmp->next;
	else
		user_trace.list = tmp->next;

	free(tmp);
}

void	xmem_free_trace(ptr_t addr, str_t file, size_t line)
{
	(void)file;
	(void)line;
	
	if (being_traced)
		xmem_trace_remove(addr);

	free(addr);
}