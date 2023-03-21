SRCS := main.c \
	_entry_.c  \
	\
	options/parse_single_option.c \
	options/sanitize.c            \
	\
	utils/get_next_argument.c \
	utils/usage.c             \
	utils/str_to_uint64.c     \
	utils/write_all.c         \
	\
	file/file_partial_mmap.c     \
	file/file_seek_and_read.c    \
	file/file_is_mmapabble.c     \
	file/file_try_open.c         \
	file/reader/reader.c         \
	file/reader/reader_destroy.c \
	file/reader/reader_init.c    \
	file/reader/reader_utils.c   \
	\
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
	/expr/ast/ast_parser.c


NAME		:= hdump
CC			:= clang
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs
LOGGING     := -D __LOGGING__
SANITIZE    := -fstack-protector-strong -fsanitize=address
CFLAGS 		:= -Wall -Wextra -Werror -O2
CFLAGS_DBG 	:= -Wall -Wextra -Werror -g3 $(LOGGING)
CFLAGS_ASAN := -Wall -Wextra -Werror -g3 $(LOGGING) $(SANITIZE)
CFLAGS_TEST := -Wall -Wextra -Werror -g3 $(SANITIZE)
LIBSTRINGF  := libs/libstringf
LIBXDUMP  := libs/libxdump


SRCS_OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I $(INCS_DIR)

all: $(NAME)

dbg: CFLAGS=$(CFLAGS_DBG)
dbg: fclean all
asan: CFLAGS=$(CFLAGS_ASAN)
asan: fclean all
test: CFLAGS=$(CFLAGS_TEST)
test: re
	(cd tests && ./tester.sh)

-include  $(SRCS_OBJS:.o=.d)

$(NAME): $(SRCS_OBJS)
	$(MAKE) -C $(LIBSTRINGF)
	$(MAKE) -C $(LIBXDUMP)
	$(CC) $(CFLAGS) $^ -o $(NAME) -L $(LIBSTRINGF) -lstringf -L $(LIBXDUMP) -lxdump
	
clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBSTRINGF)
	$(MAKE) fclean -C $(LIBXDUMP)
	rm -rf tests/outfiles
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)

re: fclean all

.PHONY	: all clean fclean re dbg asan test