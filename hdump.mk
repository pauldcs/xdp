NAME		:= hdump
CC			:= clang
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs
SANITIZER	:= -g3 -fstack-protector-strong -fsanitize=address
CFLAGS 		:= -Wall -Wextra -Werror -O3
LOGGING     := 
LIBSTRINGF  := libs/libstringf

SRCS := main.c              \
	usage.c                 \
	debug.c                 \
	core.c                  \
	hexdump.c               \
	get_next_argument.c     \
	file_partial_mmap.c     \
	file_seek_and_read.c    \
	file_is_mmapabble.c     \
	open_hexable_file.c     \
	try_parse_argument.c    \
	build_dump_structure.c  \
	start_stdin_reader.c    \
	\
	reader/reader.c         \
	reader/reader_destroy.c \
	reader/reader_init.c    \
	reader/reader_utils.c


