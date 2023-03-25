#include "xgetopts.h"
#include "xtypes.h"
#include <string.h>
#include <stdlib.h>

void xgetopts_init(t_xgetopts *opt, size_t ac, cut8 *av[], cstr_t ostr)
{
	memset(opt, 0, sizeof (t_xgetopts));
	opt->ac = --ac;
	opt->av = (ut8 **)++av;
	opt->ostr = ostr;
}
