#ifndef __SCREEN_H__
# define __SCREEN_H__

#include "xtypes.h"

typedef struct s_hexer {
	size_t   read_size;
	ptr_t    src_ptr;
	size_t   src_size
	ptr_t    screen_ptr;
	size_t   screen_size;
}	t_hexer;
#endif