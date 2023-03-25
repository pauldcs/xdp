#ifndef __USER_OPTIONS_H__
# define __USER_OPTIONS_H__

# include <stddef.h>
# include <stdbool.h>
# include "file.h"

typedef enum e_xdp_mode
{
	M_NORMAL,
	M_STRING,
	M_STREAM,
}	t_xdp_mode;

typedef struct s_user_options
{
	const char    *filename;
	t_xdp_mode    mode;
	size_t        start_offset;
	size_t        string_size;
	bool          colors;
	size_t        range;
}	t_user_options;

void 			user_options_init(t_user_options *opts);
t_user_options 	*user_options_parse(int ac, char *av[]);
bool 			user_options_within_range(t_user_options *opts, t_file *file);
void 			user_options_debug_print(t_user_options *opts);

#endif /* __USER_OPTIONS_H__ */