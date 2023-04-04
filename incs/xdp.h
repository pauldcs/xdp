#ifndef __XDP_H__
# define __XDP_H__

# include "options/user_options.h"
# include "file.h"
# include "hexxer.h"
# include <errno.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

bool    __entry__(t_user_options *opts);
bool	dump_fd(int fd, t_hexxer *hexxer);
void 	usage(void);


#endif /* __XDP_H__ */
