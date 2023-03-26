#include "xmem.h"
#include "log.h"
#include "xtypes.h"
#include <stdio.h>
#include <assert.h>

void xmem_print_summary(void)
{
	assert(allocs_are_traced != false);
	if (mem_trace.in_use.nbytes)
	{
		t_xmem_alloc *tmp = mem_trace.list;
		assert(mem_trace.list != NULL);

		fprintf(stdout, "\n%s -- [LEAK ALERT] --%s\n\n", C_BRED, C_RESET);
		while (tmp)
		{
			fprintf(stdout, 
				" - %zu bytes are leaking from address %p (%d:%s:%zu)\n",
					tmp->block_size,
					tmp->block_ptr,
					tmp->owner,
					tmp->origin.file, 
					tmp->origin.line
			);
			tmp = tmp->next;
		}
	}

	fprintf(stdout,
			"\nHEAP SUMMARY:\n"
			"    in use at exit: %zu bytes in %zu blocks\n"
			"  total heap usage: %zu allocs, %zu frees, %zu bytes allocated\n"
			"\n",
		mem_trace.in_use.nbytes,
		mem_trace.in_use.nblocks,
		mem_trace.cmalloc_n_mallocs,
		mem_trace.cmalloc_n_frees,
		mem_trace.cmalloc_bs_mallocd
	);
}
