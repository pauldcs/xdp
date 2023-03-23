SRCS := main.c \
	_entry_.c  \
	\
	options/options_struct_debug_print.c \
	options/options_within_range.c       \
	options/parse_user_options.c         \
	\
	utils/get_next_argument.c \
	utils/usage.c             \
	utils/str_to_uint64.c     \
	utils/write_all.c         \
	\
	infile/infile_read_from_offset.c      \
	infile/infile_mmap_from_offset.c      \
	infile/infile_mmap_recommended.c      \
	infile/infile_struct_debug_print.c    \
	infile/infile_get_size.c              \
	infile/infile_open.c                  \
	infile/infile_destroy.c               \
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
	/expr/ast/ast_parser.c


NAME		:= hdump
CC			:= clang
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs
LOGGING     := -D __LOGGING__
SANITIZE    := -fstack-protector-strong -fsanitize=address
CFLAGS 		:= -Wall -Wextra -Werror -g3 $(LOGGING)
CFLAGS_PROD := -Wall -Wextra -Werror -O3
CFLAGS_ASAN := -Wall -Wextra -Werror -g3 $(LOGGING) $(SANITIZE)
CFLAGS_TEST := -Wall -Wextra -Werror -g3
LIBSTRINGF  := libs/libstringf
LIBXDUMP    := libs/libxdump


SRCS_OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I $(INCS_DIR)

all: $(NAME)

prod: CFLAGS=$(CFLAGS_PROD)
prod: fclean all
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