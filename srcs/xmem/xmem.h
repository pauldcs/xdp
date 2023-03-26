#ifndef __XMEM_H__
# define __XMEM_H__

# include <stddef.h>
# include <sys/types.h>
# include <stdlib.h>
# include "xtypes.h"

typedef struct s_xmem_alloc
{
	pid_t  owner;
	ptr_t  block_ptr;
	size_t block_size;
	ut64   id;
	struct s_origin
	{
		str_t  file;
		size_t line;
	}   origin;
	struct s_xmem_alloc *next;
}	t_xmem_alloc;

typedef struct s_xmem_trace
{
	t_xmem_alloc *list;
	size_t       cmalloc_n_mallocs;
	size_t       cmalloc_n_frees;
	size_t       cmalloc_bs_mallocd;
	struct s_in_use
	{
		size_t nbytes;
		size_t nblocks;
	} in_use;
}	t_xmem_trace;

extern t_xmem_trace mem_trace;

# ifdef __XMEM__
#  define __xmalloc__(size) xmem_malloc(size, __FILE__, __LINE__)
#  define __xfree__(ptr) xmem_free(ptr)
# else
#  define __xmalloc__(size) malloc(size)
#  define __xfree__(ptr) free(ptr)
#endif

void xmem_trace_init(void);
void xmem_trace_destroy(void);
void xmem_print_summary(void);

ptr_t	xmem_realloc(ptr_t *buf, size_t *cap, size_t len, size_t new_cap);
ptr_t	xmem_malloc(size_t size, str_t file, size_t line);
void	xmem_free(ptr_t addr);

#endif /* __XMEM_H__ */