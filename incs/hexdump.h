#ifndef __HEXDUMP_H__
# define __HEXDUMP_H__

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

# define BASE "0123456789abcdef"

typedef enum e_mode {
	DUMP_CLASSIC,
	DUMP_RAW
}	t_mode;

typedef struct s_dump_params {
	t_mode 		 mode;
	const char   *filename;
	bool 		 is_stdin;
	int64_t      max_size;
	int64_t      start_offset;
	int64_t      end_offset;
}	            t_dump_params;

int hexdump(t_dump_params *params);

#endif /* __HEXDUMP_H__ */
