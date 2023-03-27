#ifndef __XLEAKS_H__
# define __XLEAKS_H__

# include <stdlib.h>
# include <string.h>
# include <sys/mman.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <stdbool.h>

# define C_BLACK     "\e[0;30m"
# define C_RED       "\e[0;31m"
# define C_BRED      "\e[1;31m"
# define C_GREEN     "\e[0;32m"
# define C_YELLOW    "\e[0;33m"
# define C_BLUE      "\e[0;34m"
# define C_MAGENTA   "\e[0;35m"
# define C_CYAN      "\e[0;36m"
# define C_LIGHTGREY "\x1b[37;1m"
# define C_WHITE     "\x1b[2;37m"
# define C_GREY      "\x1b[90m"
# define C_RESET     "\e[0m"

/*-- Wrap macros--*/
/**
 * If the flag `-D LEAK_CHECK` is passed when compiled
 * the macros will extend into the wrapper functions
 * instead of the actual ones
 */
# ifdef __LEAK_CHECK__
#  define __xfree__(ptr)           free_wrapper(ptr, __FILE__, __LINE__)
#  define __xmalloc__(size)        malloc_wrapper(size, __FILE__, __LINE__)
#  define __xrealloc__(ptr, size)  realloc(ptr, size)  /* todo */
#  define __xcalloc__(count, size) calloc(count, size) /* todo */
#  define __xstrdup__(str)         strdup(str)         /* todo */
#  define __xstrndup__(str, n)     strndup(str, n)     /* todo */
#  define __xmmap__(a,b,c,d,e,f)   mmap(a,b,c,d,e,f)   /* todo */
#  define __xmunmap__(addr, len)   munmap(addr, len)   /* todo */
//#  define __xasprintf__          asprintf()          /* todo */
#  define __xopen__(p, o, m)       open_wrapper(p, o, m, __FILE__, __LINE__)
#  define __xclose__(fd)           close_wrapper(fd, __FILE__, __LINE__)
#  define __xdup__(fd)             dup(fd)             /* todo */
#  define __xdup2__(fd_1, fd_2)    dup2(fd_1, fd_2);   /* todo */
#  define __xopendir__(name)       opendir(name)       /* todo */
#  define __xclosedir__(dirp)      closedir(dirp)      /* todo */
# else
#  define __xmalloc__(size)        malloc(size)
#  define __xrealloc__(ptr, size)  realloc(ptr, size)
#  define __xcalloc__(count, size) calloc(count, size)
#  define __xfree__(ptr)           free(ptr)
#  define __xstrdup__(str)         strdup(str)
#  define __xstrndup__(str, n)     strndup(str, n)
#  define __xmmap__(a,b,c,d,e,f)   mmap(a,b,c,d,e,f)
#  define __xmunmap__(addr, len)   munmap(addr, len)
//#  define __xasprintf__          asprintf()
//#  define __xopen__()            open()
#  define __xclose__(fd)           close(fd)
#  define __xdup__(fd)             dup(fd)
#  define __xdup2__(fd_1, fd_2)    dup2(fd_1, fd_2);
#  define __xopendir__(name)       opendir(name)
#  define __xclosedir__(dirp)      closedir(dirp)
#endif /* __LEAK_CHECK_ */

void xleaks_init(void)    __attribute__((constructor));
void xleaks_destroy(void) __attribute__((destructor));

void xleaks_state(void);
void xleaks_summary(void);

/*-- Wrappers --*/
void *malloc_wrapper(size_t size, const char *file, size_t line);
void free_wrapper(void *ptr, const char *file, size_t line);
int open_wrapper(const char *path, int oflag, mode_t mode, const char *file, size_t line);
int close_wrapper(int fildes, const char *file, size_t line);

/*-- Ressource list --*/
typedef enum e_rss_type {
	MEMORY,
	FILDES
}	t_rss_type;

typedef struct s_active_rss {
	pid_t      owner; /* owner of the rss */
	const char *file; /* file where the rss was created */
	size_t     line;  /* line where the rss was created */
	t_rss_type type;  /* the type of the rss */
	union {
		int    fd; /* the opened fd */
		struct s_mem_block {
			bool   map;  /* true if the block is mapped */
			void   *ptr; /* pointer to the memory area */
			size_t size; /* size of the memory area */
		}	block;
	} rss;
	struct s_active_rss *next;
}	t_active_rss;

typedef struct s_xleak_trace {
	size_t n_allocs;    /* total number of allocations */
	size_t n_frees;     /* total number of frees */
	size_t n_bytes;     /* total number of bytes allocated */
	t_active_rss *list; /* the list of currently used rss */
	struct s_in_use {
		size_t n_bytes;  /* number of bytes not freed yet */
		size_t n_blocks; /* number of allocs not freed yet */
		size_t n_fds;    /* number of file descriptors not closed yet*/
	} in_use;
}	t_xleak_trace;

extern t_xleak_trace xleak_trace;

void active_rss_add(t_active_rss *rss);
void active_rss_clear(void);
void active_rss_print(t_active_rss *rss);
bool active_rss_delete(void *scent, t_rss_type type);

t_active_rss *active_rss_new_fd(int fd, const char *file, size_t line);
t_active_rss *active_rss_new_mem(bool map, void *ptr, size_t size, const char *file, size_t line);

#endif /* __XLEAKS_H__ */