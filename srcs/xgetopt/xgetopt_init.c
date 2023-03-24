#include "getopt.h"
#include <string.h>
#include <stdlib.h>

void r_getopt_init(t_getopt *opt, int argc, const char **argv, const char *ostr) {
	memset (opt, 0, sizeof (t_getopt));
	opt->err = 1;
	opt->ind = 1;
	opt->opt = 0;
	opt->reset = 0;
	opt->arg = NULL;
	opt->argc = argc;
	opt->argv = argv;
	opt->ostr = ostr;
}
