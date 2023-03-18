NAME		:= hdump
CC			:= clang
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs
SANITIZER	:= -g3 -fstack-protector-strong -fsanitize=address
CFLAGS 		:= -Wall -Wextra -Werror -O3 -g3
LIBSTRINGF  := libs/libstringf

SRCS := main.c              \
	display_usage.c         \
	mem_efficient_mmap.c    \
	read_exact_range.c      \
	debug.c                 \
	should_mmap.c           \
	safe_open.c             \
	parse_single_argument.c \
	build_dump_structure.c  \
	core.c                  \
	hexdump.c               \
	read_data_from_stdin.c  \
	\
	reader/reader.c         \
	reader/reader_destroy.c \
	reader/reader_init.c    \
	reader/reader_utils.c


