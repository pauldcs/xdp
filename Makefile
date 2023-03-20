include hdump.mk

SRCS_OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I $(INCS_DIR)

all: $(NAME)

-include  $(SRCS_OBJS:.o=.d)

$(NAME): $(SRCS_OBJS)
	$(MAKE) -C $(LIBSTRINGF)
	$(CC) $(CFLAGS) $^ -o $(NAME) -L $(LIBSTRINGF) -lstringf $(SANITIZER)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBSTRINGF)
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)

re: fclean all

.PHONY	: all clean fclean re