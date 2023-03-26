#include "xmem.h"
#include "log.h"
#include "xtypes.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static void xmem_trace_add_back(t_xmem_alloc_node *node)
{
	if (!user_trace.list)
		user_trace.list = node;
	else {
		t_xmem_alloc_node *tmp = user_trace.list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

static bool xmem_trace_new_block(ptr_t *ptr, size_t nbytes, str_t file, size_t line)
{
	t_xmem_alloc_node *node = malloc(sizeof(t_xmem_alloc_node));

	if (!node) {
		log_message(fatal, "xmem_trace_new_block: Failed to allocate new block");
		return (false);
	}
	bzero(node, sizeof(t_xmem_alloc_node));

	user_trace.cmalloc_n_mallocs += 1;
	user_trace.cmalloc_bs_mallocd += nbytes;
	user_trace.in_use.nbytes += nbytes;
	user_trace.in_use.nblocks += 1;
	node->block_ptr = *ptr;
	node->owner = getpid();
	node->block_size = nbytes;
	node->origin.file = file;
	node->origin.line = line;

	xmem_trace_add_back(node);
	return (true);
}

bool	xmem_alloc_trace(ptr_t *addr, size_t size, str_t file, size_t line)
{
	if ((*addr = malloc(size)))
	{
		bzero(*addr, size);
		if (!being_traced)
			return (true);

		if (xmem_trace_new_block(addr, size, file, line))
			return (true);

		free(*addr);
	}
	log_message(fatal, "xmem_alloc_trace: Failed to allocate %zu bytes", size);
	return (false);
}
