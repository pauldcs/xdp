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
	mkdir -vp $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$(NAME)
	
clean:
	rm -rf $(OBJS_DIR)
	@true

fclean: clean
	rm -rf tests/outfiles
	rm -rf $(BUILD_DIR)
	rm -rf $(OBJS_DIR)
	@true

re: fclean all

.PHONY	: all clean fclean re asan test