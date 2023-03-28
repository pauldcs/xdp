include xleaks.mk

SRCS_OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -fPIC -o $@ -c $< -I $(INCS_DIR)

all: $(NAME)

-include  $(SRCS_OBJS:.o=.d)

$(NAME): $(SRCS_OBJS)
ifeq ($(UNAME), Darwin)
	$(CC) $(CFLAGS) -dynamiclib $(SRCS_OBJS) -o $(NAME)
else
	$(CC) $(CFLAGS) -shared $(SRCS_OBJS) -o $(NAME)
endif

clean:
	rm -rf $(OBJS_DIR)
	@true

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)
	@true

re: fclean all

.PHONY	: all clean fclean re 
