include xdp.mk

SRCS_OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I $(INCS_DIR)

all: $(NAME)

-include  $(SRCS_OBJS:.o=.d)

$(NAME): $(SRCS_OBJS)
	$(MAKE) -C $(XLEAKS_DIR)
#	$(CC) $(CFLAGS) $^ -o $(NAME) -Wl,-rpath,'$$ORIGIN' -L . -lxleaks
	$(CC) $(CFLAGS) $^ -o $(NAME)
	
clean:
	rm -rf $(OBJS_DIR)
	@true

fclean: clean
	$(MAKE) fclean -C $(XLEAKS_DIR)
	rm -rf tests/outfiles
	rm -rf $(NAME)
	rm -rf $(OBJS_DIR)
	@true

re: fclean all

.PHONY	: all clean fclean re 

#enable debug flags
g: CFLAGS += $(CFLAGS_DBG)
g: all

#enable debug flags + ASAN
g2: CFLAGS += $(CFLAGS_DBG_2)
g2: all