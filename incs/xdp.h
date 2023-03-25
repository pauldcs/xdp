#ifndef __XDP_H__
# define __XDP_H__

# include "options/user_options.h"
# include "file.h"
# include <errno.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

bool    _entry_(t_user_options *opts);
void 	usage(void);

#endif /* __XDP_H__ */
