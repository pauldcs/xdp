NAME		:= hdump
CC			:= gcc
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs
SANITIZER	:= -g3 -fstack-protector-strong -fsanitize=address
CFLAGS 		:= -Wall -Wextra -Werror -O2
LIBSTRINGF  := libs/libstringf

SRCS := main.c \
	hexdump.c  \
	\
	reader/reader.c         \
	reader/reader_destroy.c \
	reader/reader_init.c    \
	reader/reader_utils.c


