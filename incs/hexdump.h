#ifndef __HEXDUMP_H__
# define __HEXDUMP_H__

# define BASE "0123456789abcdef"

typedef enum e_mode {
	DUMP_RAW,
	CLASSIC
}	t_mode;

int hexdump(const char *filename, t_mode mode);

#endif /* __HEXDUMP_H__ */
