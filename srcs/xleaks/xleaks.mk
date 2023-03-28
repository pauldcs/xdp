LIBNAME      := libxleaks
CC			 := clang
SRCS_DIR	 := srcs
OBJS_DIR	 := .objs
INCS_DIR	 := incs
BUILD_DIR    := build
UNAME        := $(shell uname)
CFLAGS 		 := -Wall -Wextra -Werror

ifeq ($(UNAME), Darwin)
	NAME = $(LIBNAME).dylib
else
	NAME = $(LIBNAME).so
endif

SRCS := \
	xleaks/xleaks_init.c    \
	xleaks/xleaks_destroy.c \
	xleaks/xleaks_state.c   \
	xleaks/xleaks_summary.c \
	\
	wrap/malloc_wrapper.c \
	wrap/free_wrapper.c \
	wrap/open_wrapper.c \
	wrap/close_wrapper.c \
	\
	list/active_rss_add.c     \
	list/active_rss_clear.c   \
	list/active_rss_new_fd.c  \
	list/active_rss_new_mem.c \
	list/active_rss_print.c   \
	list/active_rss_delete.c \
