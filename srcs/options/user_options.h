#ifndef __USER_OPTIONS_H__
# define __USER_OPTIONS_H__

# include <stddef.h>
# include <stdbool.h>
# include "file.h"
# include "modes.h"
# include "xtypes.h"

typedef struct s_user_options
{
	t_modes mode;
	size_t  start_offset;
	size_t  range;
}	t_user_options;

void 	user_options_init(t_user_options *opts);
void 	user_options_db_print(t_user_options *opts);

#endif /* __USER_OPTIONS_H__ */