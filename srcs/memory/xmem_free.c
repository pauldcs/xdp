#include "log.h"
#include "xtypes.h"
#include <stdlib.h>

void	xmem_free(ptr_t *ptr)
{
	if (ptr)
	{
		free(*(ptr_t *)ptr);
		*(ptr_t *)ptr = NULL;
		return ;
	}
	log_message(debug, "xmem_free: Attempt to free null pointer");
}