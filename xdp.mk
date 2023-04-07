NAME		 := xdp
CC			 := clang
SRCS_DIR	 := srcs
OBJS_DIR	 := .objs
INCS_DIR	 := incs
BUILD_DIR    := build
LOGGING      := -D __LOGGING__
LEAK_CHECK   := -D __LEAK_CHECK__
XLEAKS_DIR   := srcs/xleaks
CFLAGS 		 := -Wall -Wextra -Werror -O3 -flto
CFLAGS_DBG   := -g3 $(LOGGING) $(LEAK_CHECK) 
CFLAGS_DBG_2 := -g3 $(LOGGING) $(LEAK_CHECK) -fstack-protector-strong -fsanitize=address

SRCS := main.c    \
	__entry__.c   \
	dump_live.c   \
	dump_normal.c \
	\
	\
	options/user_options_db_print.c     \
	options/xgetopts/xgetopts_init.c    \
	options/xgetopts/xgetopts_next.c    \
	\
	\
	file/file_init.c             \
	file/file_db_print.c         \
	file/file_open.c             \
	file/file_mmap_recommended.c \
	\
	expr/expr_parse.c              \
	expr/lexer/token_list_create.c \
	expr/lexer/lst_destroy.c       \
	expr/lexer/lst_size.c          \
	expr/lexer/lst_new_token.c     \
	expr/lexer/lst_add_token.c     \
	expr/ast/ast_new_operator.c    \
	expr/ast/ast_create.c          \
	expr/ast/ast_new_value.c       \
	expr/ast/ast_solve.c           \
	expr/ast/ast_destroy.c         \
	expr/ast/ast_debug.c           \
	expr/ast/ast_parser.c          \
	\
	\
	modes/conv/xd_ascii_16_bytes.c   \
	modes/conv/xd_data_16_bytes.c    \
	modes/conv/xd_data_16_bytes_color.c \
	modes/conv/xd_pointer_8_bytes.c  \
	modes/conv/xd_pointer_p8_bytes.c \
	modes/lookup/xd_B16Pair.c        \
	modes/lookup/xd_B16PairSpaced.c  \
	modes/lookup/xd_PrintByte.c      \
	modes/lookup/xd_CharColor.c      \
	modes/xd_dump_lines.c            \
	modes/xd_dump_hex_stream.c       \
	modes/xd_dump_strings.c       \
	\
	\
	hexxer/hexxer_init.c              \
	hexxer/hexxer_destroy.c           \
	hexxer/hexxer_db_print.c          \
	\
	\
	xtypes/char/char_type.c             \
	xtypes/string/xc_legal_identifier.c \
	xtypes/string/xc_legal_number.c     \
	\
	\
	log/__log__.c \
	\
	\
	utils/xwrite.c \


	
