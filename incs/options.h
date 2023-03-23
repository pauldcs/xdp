#ifndef __OPTIONS_H__
# define __OPTIONS_H__

# include <stddef.h>
# include <stdbool.h>
# include "infile.h"

typedef enum e_hdump_mode
{
	M_NORMAL,
	M_STRING,
	M_STREAM,
}	t_hdump_mode;

typedef enum e_user_option_type {
	START_OFFSET,
	RANGE,
	HELP
}   t_user_option_type;

typedef struct s_user_options
{
	const char   *filename;
	size_t       start_offset;
	size_t       range;
	t_hdump_mode mode;
}	t_user_options;

t_user_options 	*parse_user_options(int ac, char *av[]);
bool 			options_within_range(t_user_options *opts, t_infile *file);
void 			options_struct_debug_print(t_user_options *opts);

#endif /* __OPTIONS_H__ */