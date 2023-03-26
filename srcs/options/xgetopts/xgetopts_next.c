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

st32 xgetopts_next(t_xgetopts *opts) {
	st32 ret = -1;
    if (!opts->ac || !opts->av) {
        return OPT_FAIL;
    }

    opts->arg = NULL;
    ut8 *ptr = (ut8 *)*opts->av;

    while (isspace(*ptr)) {
        ++ptr;
    }

    if (*ptr == '-' && *(ptr + 1) && !*(ptr + 2)) {
        char *c = strchr(opts->ostr, *(ptr + 1));
        if (!c) {
            log_message(warning, "illegal option -- %c", *(ptr + 1));
            ++opts->av;
            return (st32)'?';
        }

        ret = *c;
        if (*(c + 1) == ':') {
            opts->arg = next_arg(&opts->ac, &opts->av);
            if (!opts->arg) {
                log_message(error, "option requires an argument -- %c", ret);
                ++opts->av;
				opts->fail = true;
                return OPT_FAIL;
            }
        }
        ++opts->av;
    } else {
        opts->arg = ptr;
        ++opts->av;
        ret = (st32)'*';
    }

    --opts->ac;
    return ret;
}