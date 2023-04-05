#ifndef __XDP_H__
# define __XDP_H__

# include "options/user_options.h"
# include "file.h"
# include "hexxer.h"
# include <errno.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

bool    __entry__(t_user_options *opts, cstr_t filename);
void 	usage(void);

bool dump_live(int fd, t_hexxer *hexxer, t_modes mode);
bool dump_normal(t_hexxer *hexxer, t_modes mode);


#endif /* __XDP_H__ */
