#include "options/user_options.h"
#include "options/xgetopts.h"
#include "expr/expr_parser.h"
#include "xmem.h"
#include "utils.h"
#include "log.h"
#include "xtypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_user_options *user_options_parse(int ac, char *av[])
{
	t_user_options *options;
	t_xgetopts     opts;
	const char     *exec_name = av[0];
	char           c;
	
	if (!xmem_alloc((void **)&options, sizeof(t_user_options)))
		return (NULL);
		
	user_options_init(options);
	xgetopts_init(&opts, ac, (cut8 **)av, "s:r:h");

	while ((c = xgetopts_next(&opts)) != -1)
	{
		switch (c)
		{
			case 's':
				if (!expr_parse(opts.arg,
						&options->start_offset)) {
					return (xmem_free(&options), NULL);
				}
			break ;
 
			case 'r':
				if (!expr_parse(opts.arg,
						&options->range)) {
					return (xmem_free(&options), NULL);
				}
			break ;
			
			case '*':
				options->filename = opts.arg;
			break ;
	
			case 'h':
			case '?':
				fprintf(
					stdout,
						"Usage: %s [OPTIONS] FILE\n\n"
						"Description:\n"
						"    Display the contents of a file in hexadecimal format.\n\n"
						"Options:\n"
						"    -r   EXPR  Maximum number of bytes to read from the file (default: unlimited).\n"
						"    -s   EXPR  Starting byte offset to read from (default: 0).\n"
						"    -h         Show this help message\n\n",
					exec_name
				);
				xmem_free(&options);
				exit(0);
			__builtin_unreachable();
		}
	}
	
	if (opts.fail)
	{
		log_message(fatal, "incorrect arguments");
		xmem_free(&options);
		return (NULL);
	}

	return (options);
	if (!options->filename)
	{
		log_message(fatal, "No input file");
		xmem_free(&options);
		return (NULL);
	}
	return (options);
}