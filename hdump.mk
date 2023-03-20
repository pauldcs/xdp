NAME		:= hdump
CC			:= clang
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs
LOGGING     := -D __LOGGING__
CFLAGS 		:= -Wall -Wextra -Werror -O3
CFLAGS_DBG 	:= $(CFLAGS) $(LOGGING)
CFLAGS_ASAN := $(CFLAGS_DBG) -fstack-protector-strong -fsanitize=address
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
	arguments/parse_expr/lexer/token_list_create.c   \
	arguments/parse_expr/lexer/list/lst_destroy.c    \
	arguments/parse_expr/lexer/list/lst_size.c       \
	arguments/parse_expr/lexer/list/lst_new_token.c  \
	arguments/parse_expr/lexer/list/lst_add_token.c  \
	arguments/parse_expr/lexer/is_%/is_space.c       \
	arguments/parse_expr/lexer/is_%/is_oparen.c      \
	arguments/parse_expr/lexer/is_%/is_cparen.c      \
	arguments/parse_expr/lexer/is_%/is_number.c      \
	arguments/parse_expr/lexer/is_%/is_operator.c    \
	arguments/parse_expr/ast/ast_new_operator.c      \
	arguments/parse_expr/ast/ast_create.c            \
	arguments/parse_expr/ast/ast_new_value.c         \
	arguments/parse_expr/ast/ast_solve.c             \
	arguments/parse_expr/ast/ast_debug.c             \
	arguments/parse_expr/expr_parser.c               \
	arguments/parse_argument.c                       \
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


