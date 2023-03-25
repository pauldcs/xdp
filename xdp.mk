NAME		:= xdp
CC			:= clang
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs
BUILD_DIR   := build
LOGGING     := -D __LOGGING__
SANITIZE    := -fstack-protector-strong -fsanitize=address
CFLAGS 		:= -Wall -Wextra -Werror $(LOGGING)
CFLAGS_PROD := -Wall -Wextra -Werror -O3
CFLAGS_ASAN := -Wall -Wextra -Werror -g3 $(LOGGING) $(SANITIZE)
CFLAGS_TEST := -Wall -Wextra -Werror

SRCS := main.c \
	_entry_.c  \
	\
	options/user_options_debug_print.c  \
	options/user_options_within_range.c \
	options/user_options_parse.c        \
	options/user_options_init.c         \
	options/xgetopts/xgetopts_init.c    \
	options/xgetopts/xgetopts_next.c    \
	\
	utils/__usage.c           \
	utils/write_all.c         \
	utils/str_to_uint64.c     \
	\
	string/string_dump.c         \
	string/string_pattern_cmp.c  \
	string/string_distance_cmp.c \
	\
	file/manip/file_open_append.c   \
	file/manip/file_open_write.c    \
	file/manip/file_open_read.c     \
	file/status/file_exists.c       \
	file/status/file_is_directory.c \
	file/status/file_is_regular.c   \
	file/status/file_get_size.c     \
	file/file_init.c                \
	file/file_destroy.c             \
	file/file_mmap_from_offset.c    \
	file/file_mmap_recommended.c    \
	file/file_read_from_offset.c    \
	file/file_debug_print.c         \
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
	hex/conv/xd_ascii_16_bytes.c      \
	hex/conv/xd_data_16_bytes.c       \
	hex/conv/xd_pointer_8_bytes.c     \
	hex/conv/xd_pointer_p8_bytes.c    \
	hex/dump/xd_dump_lines.c          \
	hex/lookup/xd_B16Pair.c     \
	hex/lookup/xd_B16PairSpaced.c     \
	hex/lookup/xd_PrintByte.c         \
	\
	xtypes/char/char_type.c             \
	xtypes/string/xc_legal_identifier.c \
	xtypes/string/xc_legal_number.c     \
	\
	log/log_message.c \
	\
	memory/xmem_alloc.c   \
	memory/xmem_free.c    \
	memory/xmem_realloc.c \

	
