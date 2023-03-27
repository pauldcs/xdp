#include "xleaks.h"
#include <stdio.h>

__attribute__((destructor))
void xleaks_destroy(void)
{
	xleaks_state();
	xleaks_summary();
	active_rss_clear();
	return ;
}