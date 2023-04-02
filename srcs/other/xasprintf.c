#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "xtypes.h"

st8 *xasprintf(cut8 *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	char *res;
	if (vasprintf(&res, fmt, ap) < 0)
		return (NULL);

	va_end(ap);
	return res;
}