#ifndef __XDP_H__
# define __XDP_H__

# include "options/user_options.h"
# include "file.h"
# include "hex.h"
# include <errno.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

bool    __entry__(t_user_options *opts);
void 	usage(void);
ssize_t	xd_dump_lines(const uint8_t *addr, size_t n, size_t offset, ut8 *__scr_ptr, size_t scr_size);

#endif /* __XDP_H__ */
