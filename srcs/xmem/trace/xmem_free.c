#include "xmem.h"
#include "log.h"
#include "xtypes.h"
#include <stdlib.h>
#include <assert.h>

static void xmem_trace_remove(ptr_t ptr)
{
	assert (mem_trace.list != NULL && "Trace list is null ?");

	t_xmem_alloc *tmp = mem_trace.list;
	t_xmem_alloc *prev = NULL;

	while (tmp && tmp->block_ptr != ptr)
	{
		prev = tmp;
		tmp = tmp->next;
	}

	assert(tmp != NULL && "The block was not in the trace list");

	mem_trace.cmalloc_n_frees += 1;
	mem_trace.in_use.nblocks  -= 1;
	mem_trace.in_use.nbytes   -= tmp->block_size;

	if (prev)
		prev->next = tmp->next;
	else
		mem_trace.list = tmp->next;
	free(tmp);
}

void	xmem_free(ptr_t addr)
{
	xmem_trace_remove(addr);
	free(addr);
}