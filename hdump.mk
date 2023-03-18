NAME		:= hdump
CC			:= clang
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs
SANITIZER	:= -g3 -fstack-protector-strong -fsanitize=address
CFLAGS 		:= -Wall -Wextra -Werror
LIBSTRINGF  := libs/libstringf

SRCS := main.c              \
	usage.c                 \
	debug.c                 \
	core.c                  \
	hexdump.c               \
	get_next_argument.c     \
	memory_efficient_mmap.c \
	read_range_only.c       \
	should_use_mmap.c       \
	safe_open.c             \
	try_parse_argument.c    \
	build_dump_structure.c  \
	read_data_from_stdin.c  \
	\
	reader/reader.c         \
	reader/reader_destroy.c \
	reader/reader_init.c    \
	reader/reader_utils.c


