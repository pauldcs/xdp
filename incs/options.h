#ifndef __OPTIONS_H__
# define __OPTIONS_H__

# include "hdump.h"
# include "file/file.h"
# include <stdbool.h>

typedef enum e_hd_display_mode
{
	M_NORMAL,
	M_STRING,
	M_STREAM,
}	t_hd_display_mode;

typedef struct s_hd_opts
{
	t_hd_display_mode  mode;
	t_hd_file 		   file;
}	t_hd_opts;

bool parse_single_option(const char *str, t_hd_opts *opts, int *ac, char ***av);
bool sanitize(t_hd_opts *opts);

#endif /* __OPTIONS_H__ */