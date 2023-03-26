#include "xmem.h"
#include "log.h"
#include <string.h>
#include <assert.h>

t_xmem_trace user_trace;
bool         being_traced = false;

void xmem_trace_init(void)
{
	being_traced = true;
	memset(&user_trace, 0, sizeof(user_trace));
}