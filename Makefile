include xdp.mk

SRCS_OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I $(INCS_DIR)

all: $(NAME)

prod: CFLAGS=$(CFLAGS_PROD)
prod: all

asan: CFLAGS=$(CFLAGS_ASAN)
asan: all

-include  $(SRCS_OBJS:.o=.d)

$(NAME): $(SRCS_OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)
	
clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf tests/outfiles
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)

re: fclean all

.PHONY	: all clean fclean re asan test