#include "hex.h"
#include "log.h"
#include "xleaks.h"
#include "xtypes.h"

void hexxer_destroy(t_hexxer *hexxer)
{
	if (hexxer == NULL)
		return;

	if (hexxer->mapped)
	{
		munmap(hexxer->data.ptr, hexxer->data.cap);
		hexxer->data.ptr = NULL;

	} else {
		__xfree__(hexxer->data.ptr);
		hexxer->data.ptr = NULL;
	}
	
	if (hexxer->screen.ptr) {
		__xfree__(hexxer->screen.ptr);
		hexxer->screen.ptr = NULL;
	}
}
