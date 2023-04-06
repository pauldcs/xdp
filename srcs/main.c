#include "xdp.h"
#include "log.h"
#include "xleaks.h"
#include "xtypes.h"
#include "expr/expr.h"
#include "options/xgetopts.h"
#include "options/user_options.h"
#include <stdlib.h>

# define FILE_STACK_SIZE 16

static ptr_t  __stack[FILE_STACK_SIZE];
static size_t __top;

static void __push_filename(str_t filename)
  {
	if (__top < FILE_STACK_SIZE - 1) __stack[++__top] = filename;
  }
static ptr_t __pop_filename(void)
  {
	if (__top > 0) return ((ptr_t)__stack[__top--]);
	return (NULL);
  }

t_user_options *user_options_parse(int ac, char *av[])
{
	t_user_options *options = __xmalloc__(sizeof(t_user_options));
	t_xgetopts opts;
	char ch;
	
	if (!options) return (NULL);
		
	bzero(options, sizeof(t_user_options));
	xgetopts_init(&opts, ac, (cut8 **)av, "o:n:srh");

	while ((ch = xgetopts_next(&opts)) != (char)-1)
	{
		switch (ch) {
		case 'o':
			if (expr_parse(opts.arg, &options->start_offset) == false)
				return (
					__xfree__(options),
					NULL
				);
		break;	
		case 'n':
			if (expr_parse(opts.arg, &options->range) == false)
				return (
					__xfree__(options),
					NULL
				);
		break;
		case 'r': options->mode = XDP_STREAM; break;	
		case 's': options->mode = XDP_STRINGS; break;	
		case '*':
			/*
			 * We can assume it's a filename
			 * if it does not match any of the 
			 * options.
			 */
			if (__top == FILE_STACK_SIZE) break;
			if (opts.arg == NULL
				|| !strcmp(opts.arg, "-")
				|| !strcmp(opts.arg, "stdin"))
				__push_filename(NULL);
			else
				__push_filename(opts.arg);
			break;
		case 'h':
		case '?':
			__xfree__(options);
			usage();
			/* NOT REACHED */
		}
	}
	
	if (opts.fail)
	{
		__log__(fatal, "Invalid arguments");
		__xfree__(options);
		return (NULL);
	}

	return (options);
}

int main(int ac, char *av[])
{	
	t_user_options *options = user_options_parse(ac, av);

	if (options == NULL)
		return (EXIT_FAILURE);
	
	size_t tmp_range = options->range;
	bool success;

	for (;;)
	{
		options->range = tmp_range;
		success = __entry__(
			options,
			__pop_filename()
		);
		if (!__top) break;
	}

	int retval = success == false;
	__xfree__(options);
	return (retval);
}

void
usage(void)
{
	(void)fprintf(stderr,
		"Usage: xdp [-hns] [-on expr] [file ...]\n\n"
		"Description:\n"
		"    Display the contents of a file in hexadecimal format.\n\n"
		"Options:\n"
		"    -n  EXPR  The range of bytes to read from the file (default: unlimited).\n"
		"    -o  EXPR  Starting byte offset to read from (default: 0).\n"
		"    -s        Dump strings at least 4 characters long.\n"
		"    -r        Dump as a stream of hex characters.\n"
		"    -h        Show this help message\n\n"
	);
	exit(1);
}

