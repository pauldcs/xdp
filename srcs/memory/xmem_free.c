#include <stdlib.h>

void	xmem_free(void *ptr)
{
	if (ptr)
	{
		free(*(void **)ptr);
		*(void **)ptr = NULL;
	}
}