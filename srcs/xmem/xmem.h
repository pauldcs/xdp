#ifndef __XMEM_H__
# define __XMEM_H__

# include <stddef.h>
# include "xtypes.h"

bool	re_alloc(ptr_t *buf, size_t *cap, size_t len, size_t new_cap);
bool	xmem_alloc(ptr_t *ptr, size_t size);
void	xmem_free(ptr_t ptr);

#endif /* __XMEM_H__ */