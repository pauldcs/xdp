#include "xmem.h"
#include "log.h"
#include <string.h>
#include <assert.h>

t_xmem_trace mem_trace;
bool         allocs_are_traced = false;

void xmem_trace_init(void)
{
	allocs_are_traced = true;
	log_message(warning, "Memory tracing enabled");
	memset(&mem_trace, 0, sizeof(mem_trace));
}