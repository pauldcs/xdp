#include "xmem.h"
#include "log.h"
#include <string.h>
#include <assert.h>

t_xmem_trace mem_trace;

void xmem_trace_init(void)
{
	log_message(warning, "Memory tracing enabled");
	memset(&mem_trace, 0, sizeof(mem_trace));
}