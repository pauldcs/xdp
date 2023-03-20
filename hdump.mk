NAME		:= hdump
CC			:= clang
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs
SANITIZER	:= -fstack-protector-strong -fsanitize=address
LOGGING     := -D __LOGGING__
CFLAGS 		:= -Wall -Wextra -Werror -O3 -g3
LIBSTRINGF  := libs/libstringf

SRCS := main.c              \
	hex_core.c              \
	dump.c                  \
	file_partial_mmap.c     \
	file_seek_and_read.c    \
	file_is_mmapabble.c     \
	open_hexable_file.c     \
	build_dump_structure.c  \
	start_stdin_reader.c    \
	dump_strings.c          \
	\
	arguments/parse_argument.c \
	\
	utils/get_next_argument.c \
	utils/usage.c             \
	utils/str_to_uint64.c     \
	utils/write_all.c         \
	\
	reader/reader.c         \
	reader/reader_destroy.c \
	reader/reader_init.c    \
	reader/reader_utils.c   


