NAME		:= xdp
CC			:= clang
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs
LOGGING     := -D __LOGGING__
SANITIZE    := -fstack-protector-strong -fsanitize=address
CFLAGS 		:= -Wall -Wextra -Werror $(LOGGING)
CFLAGS_PROD := -Wall -Wextra -Werror -O3
CFLAGS_ASAN := -Wall -Wextra -Werror -g3 $(LOGGING) $(SANITIZE)
CFLAGS_TEST := -Wall -Wextra -Werror

SRCS := main.c \
	_entry_.c  \
	\
	options/options_struct_debug_print.c \
	options/options_within_range.c       \
	options/parse_user_options.c         \
	\
	utils/get_next_argument.c \
	utils/usage.c             \
	utils/write_all.c         \
	utils/str_to_uint64.c     \
	\
	strdump/str_dump.c      \
	strdump/strp_compare.c  \
	strdump/strd_compare.c  \
	\
	infile/infile_read_from_offset.c   \
	infile/infile_mmap_from_offset.c   \
	infile/infile_mmap_recommended.c   \
	infile/infile_struct_debug_print.c \
	infile/infile_get_size.c           \
	infile/infile_open.c               \
	infile/infile_destroy.c            \
	\
	/expr/expr_parse.c              \
	/expr/lexer/token_list_create.c \
	/expr/lexer/lst_destroy.c       \
	/expr/lexer/lst_size.c          \
	/expr/lexer/lst_new_token.c     \
	/expr/lexer/lst_add_token.c     \
	/expr/ast/ast_new_operator.c    \
	/expr/ast/ast_create.c          \
	/expr/ast/ast_new_value.c       \
	/expr/ast/ast_solve.c           \
	/expr/ast/ast_debug.c           \
	/expr/ast/ast_parser.c          \
	\
	hexdump/conv/xd_ascii_16_bytes.c      \
	hexdump/conv/xd_data_16_bytes.c       \
	hexdump/conv/xd_pointer_8_bytes.c     \
	hexdump/conv/xd_pointer_p8_bytes.c    \
	hexdump/dump/xd_dump_lines.c          \
	hexdump/lookup/xd_B16Pair.c     \
	hexdump/lookup/xd_B16PairSpaced.c     \
	hexdump/lookup/xd_PrintByte.c         \
	\
	xtypes/char/char_type.c             \
	xtypes/string/xc_legal_identifier.c \
	xtypes/string/xc_legal_number.c     \
	
