#include "getopt.h"
#include <stdlib.h>

#define	BADCH	(int)'?'
#define	BADARG	(int)':'
#define	EMSG	""

int xgetopt_next(t_getopt *opt) {
	static const char *place = EMSG; // option letter processing
	const char *oli; // option letter list index

	if (opt->reset || !*place) { // update scanning pointer
		opt->reset = 0;
		if (opt->ind >= opt->argc || *(place = opt->argv[opt->ind]) != '-') {
			place = EMSG;
			return -1;
		}
		if (place[1] && *++place == '-') { // found "--"
			opt->ind++;
			place = EMSG;
			return -1;
		}
	}
	/* option letter okay? */
	if ((opt->opt = (int)*place++) == (int)':' || !(oli = strchr (opt->ostr, opt->opt))) {
		/*
		 * if the user didn't specify '-' as an option,
		 * assume it means -1.
		 */
		if (opt->opt == '-') {
			return -1;
		}
		if (!*place) {
			opt->ind++;
		}
		if (opt->err && *opt->ostr != ':') {
			(void)eprintf ("%s: illegal option -- %c\n", opt->argv[0], opt->opt);
		}
		return BADCH;
	}
	if (*++oli == ':') { /* need argument */
		if (*place) { /* no white space */
			opt->arg = place;
		} else if (opt->argc <= ++opt->ind) {  /* no arg */
			place = EMSG;
			if (*opt->ostr == ':') {
				return BADARG;
			}
			if (opt->err) {
				(void)eprintf ("%s: option requires an argument -- %c\n", opt->argv[0], opt->opt);
			}
			return BADCH;
		} else { /* white space */
			opt->arg = opt->argv[opt->ind];
		}
		place = EMSG;
		opt->ind++;
	} else {
		opt->arg = NULL;
		if (!*place) {
			opt->ind++;
		}
	}
	// dump back option letter
	return opt->opt;
}
