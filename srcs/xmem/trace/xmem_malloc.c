#include "xmem.h"
#include "log.h"
#include "xtypes.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static void xmem_trace_add_back(t_xmem_alloc *new_alloc)
{
	if (!mem_trace.list)
		mem_trace.list = new_alloc;
	else {
		t_xmem_alloc *tmp = mem_trace.list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_alloc;
	}
}

static bool xmem_trace_new_block(ptr_t ptr, size_t nbytes, str_t file, size_t line)
{
	static ut64 i = 0;
	t_xmem_alloc *new_alloc = malloc(sizeof(t_xmem_alloc));

	if (!new_alloc) {
		__log__(fatal, "xmem_trace_new_block: Failed to allocate new block");
		return (false);
	}
	bzero(new_alloc, sizeof(t_xmem_alloc));

	mem_trace.in_use.nblocks     += 1;
	mem_trace.in_use.nbytes      += nbytes;
	mem_trace.cmalloc_bs_mallocd += nbytes;
	mem_trace.cmalloc_n_mallocs  += 1;
	new_alloc->owner              = getpid();
	new_alloc->origin.file        = file;
	new_alloc->origin.line        = line;
	new_alloc->block_ptr          = ptr;
	new_alloc->block_size         = nbytes;
	new_alloc->id                 = ++i;

	xmem_trace_add_back(new_alloc);
	return (true);
}

ptr_t	xmem_malloc(size_t size, str_t file, size_t line)
{
	ptr_t addr = malloc(size);
	if (addr)
	{
		bzero(addr, size);

		if (xmem_trace_new_block(addr, size, file, line))
			return (addr);
		
		free(addr);
	}
	__log__(fatal, "xmem_alloc_trace: Failed to allocate %zu bytes", size);
	return (NULL);
}
