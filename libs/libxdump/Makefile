NAME		:= libxdump.a
CC			:= clang
CFLAGS 		:= -Wall -Wextra -Werror

SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs

SRCS := \
	lookup/xd_PrintByte.c          \
	lookup/xd_B16Pair.c            \
	lookup/xd_B16PairSpaced.c      \
	lookup/xd_CharColor.c       \
	lookup/xd_CharType.c           \
	\
	conv/xd_ascii_16_bytes.c       \
	conv/xd_data_16_bytes.c        \
	conv/xd_data_16_bytes_color.c  \
	conv/xd_pointer_8_bytes.c      \
	conv/xd_pointer_p8_bytes.c     \
	\
	hexdump/xd_dump_lines.c        \
	hexdump/xd_dump_lines_color.c  \

SRCS_OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	$(CC) $(CFLAGS) -o $@ -MMD -c $< -I $(INCS_DIR)

all: $(NAME)

$(NAME): $(SRCS_OBJS)
	ar rc $(NAME) $(SRCS_OBJS)

clean:
	rm -f $(SRCS_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)
	rm -rf *.dSYM

re: fclean all

.PHONY	: all clean fclean re