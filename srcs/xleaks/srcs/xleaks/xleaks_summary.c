#include "xleaks.h"
#include <stdio.h>

void xleaks_summary(void)
{
	fprintf(stdout,
			"\nHEAP SUMMARY:\n"
			"    in use at exit: %zu bytes in %zu blocks\n"
			"  total heap usage: %zu allocs, %zu frees, %zu bytes allocated\n"
			"\n",
		xleak_trace.in_use.n_bytes,
		xleak_trace.in_use.n_blocks,
		xleak_trace.n_allocs,
		xleak_trace.n_frees,
		xleak_trace.n_bytes
	);
}