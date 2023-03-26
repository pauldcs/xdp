#include "log.h"
#include "xtypes.h"
#include <stdlib.h>

void	xmem_free(ptr_t addr)
{
	if (addr)
	{
		free(*(void **)addr);
		*(void **)addr = NULL;
		return ;
	}
	log_message(debug, "xmem_free: Attempt to free null pointer");
}