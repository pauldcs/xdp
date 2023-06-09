#include "xleaks.h"
#include <string.h>
#include <stdio.h>

t_xleak_trace xleak_trace;

__attribute__((constructor))
void xleaks_init(void)
{
	bzero(&xleak_trace, sizeof(t_xleak_trace));
	return ;
}