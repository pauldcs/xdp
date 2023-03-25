# include "options.h"
# include "utils.h"
# include "log.h"
# include "xdp.h"
# include "expr/expr_parser.h"
# include <stdlib.h>
# include <string.h>

static bool __option_is(const char *arg, const char *option_name)
{
    return (!strcmp(arg, option_name) ? true : false);
}

static bool parse_argument_expr(const char *arg, void *dst)
{
	if (!arg || !expr_parse(arg, dst))
		return (false);
	
	return (true);
}
t_user_options *parse_user_options(int ac, char *av[])
{
	t_user_options *options = malloc(sizeof(t_user_options));
	
	if (!options)
		return (NULL);

	memset(options, 0x00, sizeof(t_user_options));

	while (ac && av)
	{
		if (__option_is("-s", *av) 
			|| __option_is("--start", *av))
		{
			log_message(debug, "parsing '--start'");
			if (!parse_argument_expr(
					get_next_argument(&ac, &av),
					&options->start_offset))
				return (
					free(options),
					NULL);
			else {
				--ac;
				++av;
				continue ;
			}
		
		}
		if (__option_is("-n", *av) 
			|| __option_is("--size", *av))
		{
			log_message(debug, "parsing '--range'");
			if (!parse_argument_expr(
					get_next_argument(&ac, &av),
					&options->range))
				return (
					free(options),
					NULL);
			else {
				--ac;
				++av;
				continue ;
			}
		}
		if (__option_is("-str", *av) 
			|| __option_is("--string", *av))
		{
			log_message(debug, "parsing '--string'");
			options->mode = M_STRING;
			if (!parse_argument_expr(
					get_next_argument(&ac, &av),
					&options->string_size))
				return (
					free(options),
					NULL);
			else {
				--ac;
				++av;
				continue ;
			}
		}
		if (__option_is("-c", *av)
            || __option_is("--color", *av))
		{
			options->colors = true;
			--ac;
			++av;
			continue ;
		}
		if (__option_is("-h", *av)
            || __option_is("--help", *av))
		{
			free(options);
        	usage();
       		exit (0);
	
		}
		
		if (!options->filename) {
			options->filename = *av;
			--ac;
			++av;
			continue ;
		}	
		
		log_message(fatal,  "%s: Invalid argument", *av);
		return (
			free(options),
			NULL);
	}
	return (options);
}