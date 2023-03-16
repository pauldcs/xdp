NAME		:= hdump
CC			:= gcc
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs
CFLAGS 		:= -Wall -Wextra -Werror -O2 -fsanitize=address

SRCS := main.c \
	hexdump.c


