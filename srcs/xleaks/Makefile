include xleaks.mk

SRCS_OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I $(INCS_DIR)

all: $(NAME)

-include  $(SRCS_OBJS:.o=.d)

$(NAME): $(SRCS_OBJS)
	@mkdir -vp $(BUILD_DIR)
	$(CC) $(CFLAGS) -dynamiclib $(SRCS_OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)
	@true

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJS_DIR)
	@true

re: fclean all

.PHONY	: all clean fclean re 