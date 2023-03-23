#ifndef __XDP_H__
# define __XDP_H__

# include "libs/libstringf.h"
# include "options.h"
# include "infile.h"
# include <errno.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define GRY "\x1b[2;37m"
# define END "\e[0m"

bool    _entry_(t_user_options *opts);
void 	usage(void);

#endif /* __HEXDUMP_H__ */
