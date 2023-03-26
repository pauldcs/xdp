#ifndef __XGETOPT_H__
# define __XGETOPT_H__

# include "xtypes.h"
# include <stddef.h>

# define OPT_FAIL -1

typedef struct s_xgetopts {
	bool    fail;
	ptr_t   arg;
	size_t  ac;
	ut8    	**av;
	cstr_t 	ostr;
} t_xgetopts;

void xgetopts_init(t_xgetopts *opt, size_t ac, cut8 *av[], cstr_t ostr);
st32 xgetopts_next(t_xgetopts *opt);

#endif /* __XGETOPT_H__ */