#include "xmem.h"
#include "log.h"
#include "xtypes.h"
#include <stdio.h>
#include <assert.h>

void xmem_trace_summary(void)
{
	assert(being_traced != false);
	if (user_trace.in_use.nbytes)
	{
		assert(user_trace.list != NULL);
		t_xmem_alloc_node *tmp = user_trace.list;

		fprintf(stdout, "\n%sLEAK ALERT%s\n\n",
			C_BRED,
			C_RESET);
		while (tmp)
		{
			fprintf(stdout, 
				"  - %zu bytes are leaking from address %p (%d:%s:%zu)\n",
					tmp->block_size,
					tmp->block_ptr,
					tmp->owner,
					tmp->origin.file, 
					tmp->origin.line)
			;
			tmp = tmp->next;
		}
	}

	fprintf(stdout,
			"\nHEAP SUMMARY:\n"
			"    in use at exit: %zu bytes in %zu blocks\n"
			"  total heap usage: %zu allocs, %zu frees, %zu bytes allocated\n"
			"\n",
		user_trace.in_use.nbytes,
		user_trace.in_use.nblocks,
		user_trace.cmalloc_n_mallocs,
		user_trace.cmalloc_n_frees,
		user_trace.cmalloc_bs_mallocd
	);
}
