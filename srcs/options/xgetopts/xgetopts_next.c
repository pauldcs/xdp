#include "log.h"
#include "xgetopts.h"
#include "xtypes.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static ut8 *next_arg(size_t *ac, ut8 ***av)
{
	if (*ac)
	{
		--(*ac);
		return ((ut8 *)*++*av);
	}
	return (0);
}

st32 xgetopts_next(t_xgetopts *opts)
{
	char *c;
	st32 ret;
	
	if (!opts->ac || !opts->av)
		return (OPT_FAIL);
	
	opts->arg = NULL;
	ut8 *ptr = (ut8 *)*opts->av;

	while (isspace(*ptr))
		ptr++;

	if (*ptr == '-' && *(++ptr) && !*(ptr + 1))
	{
		c = strchr(opts->ostr, *ptr);
		if (c == NULL) 
		{
			ret = (st32)'?';
			log_message(warning, "illegal option -- %c", *ptr);
		} else {
			ret = *c;
			if (*(c + 1) == ':')
			{
				opts->arg = next_arg(&opts->ac, &opts->av);
				if (!opts->arg)
				{
					log_message(error, "option requires an argument -- %c", *c);
					return (OPT_FAIL);
				}
			}
		}
	} else {
		opts->arg = ptr;
		ret = (st32)'*';
	}
	opts->ac--;
	opts->av++;
	return (ret);
}