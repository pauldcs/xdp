NAME		 := libxleaks.dylib
CC			 := clang
SRCS_DIR	 := srcs
OBJS_DIR	 := .objs
INCS_DIR	 := incs
BUILD_DIR    := build
CFLAGS 		 := -Wall -Wextra -Werror

SRCS := \
	xleaks/xleaks_init.c    \
	xleaks/xleaks_destroy.c \
	xleaks/xleaks_state.c   \
	xleaks/xleaks_summary.c \
	\
	wrap/malloc_wrapper.c \
	wrap/free_wrapper.c \
	\
	list/active_rss_add.c     \
	list/active_rss_clear.c   \
	list/active_rss_new_fd.c  \
	list/active_rss_new_mem.c \
	list/active_rss_print.c   \
	list/active_rss_delete.c \
