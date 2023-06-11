#include "xdp.h"
#include "log.h"
#include "xleaks.h"
#include "xtypes.h"
#include "expr/expr.h"
#include "options/xgetopts.h"
#include "options/user_options.h"
#include <stdlib.h>

# define FILE_STACK_SIZE 16 /* can be increased */
/*
 *    mini stack to hold each file
 *    to dump separatly
 */
static void*  __stack[FILE_STACK_SIZE];
static size_t __top;

static void __push_filename(str_t filename) {
	if (__top < FILE_STACK_SIZE - 1) __stack[++__top] = filename;
}
static ptr_t __pop_filename(void) {
	if (__top > 0) return ((ptr_t)__stack[__top--]);
	return (NULL);
}

void reverseStack() {
    size_t i = 1;
    size_t j = __top;
    void* tmp;

    while (i < j) {
        tmp = __stack[i];
        __stack[i] = __stack[j];
        __stack[j] = tmp;
        i++;
        j--;
    }
}

t_user_options *user_options_parse(int ac, char *av[])
{
	t_user_options *options = __xmalloc__(sizeof(t_user_options));
	t_xgetopts opts;
	char ch;
	
	if (!options) return (NULL);
		
	bzero(options, sizeof(t_user_options));

	xgetopts_init(&opts, ac, (cut8 **)av, "o:n:srhcx");

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
		case 'c': options->color = true; break;
		case '*':
			/*
			 *     if it does not match any of the 
			 *     options it's a filename
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
	/* 
	 *     params that come after argument 
	 *     parsing are filenames
	 */
	while (*opts.av++ && *opts.av) 
		__push_filename((char *)*opts.av);
	return (options);
}

int main(int ac, char *av[])
{	
	t_user_options *options = user_options_parse(ac, av);

	if (options == NULL)
		return (EXIT_FAILURE);
	
	size_t tmp_range = options->range;
	bool success;

	reverseStack();
	for (;;)
	{
		options->range = tmp_range;
		char *file = __pop_filename();
		success = __entry__(
			options,
			file
		);
		if (!__top) break;
	}
	__xfree__(options);
	return (success);
}

void
usage(void)
{
	(void)fprintf(stderr,
		"usage: xdp [-hncs] [-o offset] [-n length] ... [file] ...\n\n"
		"description:\n"
		"    touch the very fabric of creation itself, follow the\n"
		"    darkest depths and wield a power that few can comprehend\n\n"
		"options:\n"
		"    -n  EXPR  the range of bytes to read from the file (default: until EOF)\n"
		"    -o  EXPR  starting byte offset to read from (default: 0)\n"
		"    -s        dump strings at least 4 characters long\n"
		"    -c        enable colored output\n"
		"    -r        dump as a stream of hex characters\n"
		"    -h        show this help message\n\n"
	);
	exit(1);
}

