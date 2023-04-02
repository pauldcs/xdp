#ifndef __XDP_H__
# define __XDP_H__

# include "options/user_options.h"
# include "file.h"
# include <errno.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

bool    __entry__(t_user_options *opts);
void 	usage(void);
bool    hexdump(int fd, size_t size, size_t start_offset);

#endif /* __XDP_H__ */
