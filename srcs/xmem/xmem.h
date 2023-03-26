#ifndef __XMEM_H__
# define __XMEM_H__

# include <stddef.h>
# include <sys/types.h>
# include "xtypes.h"

typedef struct s_xmem_alloc_node
{
	pid_t  owner;
	ptr_t  block_ptr;
	size_t block_size;
	struct s_origin
	{
		str_t  file;
		size_t line;
	}   origin;
	struct s_xmem_alloc_node *next;
}	t_xmem_alloc_node;

typedef struct s_xmem_trace
{
	struct s_in_use
	{
		size_t   nbytes;
		size_t   nblocks;
	} in_use;
	size_t  cmalloc_n_mallocs;
	size_t  cmalloc_n_frees;
	size_t  cmalloc_bs_mallocd;

	t_xmem_alloc_node *list;
}	t_xmem_trace;

extern t_xmem_trace user_trace;
extern bool         being_traced;

# define xmem_alloc(addr, size) xmem_alloc_trace(addr, size, __FILE__, __LINE__)
# define xmem_free(addr)        xmem_free_trace(addr, __FILE__, __LINE__)

void xmem_trace_init(void);
void xmem_trace_summary(void);

bool	xmem_realloc(ptr_t *buf, size_t *cap, size_t len, size_t new_cap);
bool	xmem_alloc_trace(ptr_t *addr, size_t size, str_t file, size_t line);
void	xmem_free_trace(ptr_t addr, str_t file, size_t line);

#endif /* __XMEM_H__ */