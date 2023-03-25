#include "options/user_options.h"
#include "options/xgetopts.h"
#include "expr/expr_parser.h"
#include "utils.h"
#include "log.h"
#include "xtypes.h"
#include <stdlib.h>
#include <string.h>

t_user_options *user_options_parse(int ac, char *av[])
{
	t_user_options *options;
	t_xgetopts     opts;
	char           c;
	
	options = malloc(sizeof(t_user_options));
	if (!options)
		return (NULL);

	user_options_init(options);

	xgetopts_init(
		&opts,
		ac,
		(cut8 **)av,
		"s:n:h"
		);

	while ((c = xgetopts_next(&opts)) != OPT_FAIL)
	{
		switch (c) {
		case 's': 
			if (!expr_parse(opts.arg, &options->start_offset))
				return (free(options), NULL);
		break; 
		case 'n':
			if (!expr_parse(opts.arg, &options->range))
				return (free(options), NULL);
		break;
		case 'h':
			__usage();
			free(options);
			exit(0);
		case '*': 
			options->filename = opts.arg;
			break ;
		}
	}
	return (options);
}