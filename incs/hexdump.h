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
	bool 		 is_stdin;
	const char   *filename;
	int 		 fd;
	void         *map;
	int64_t      actual_size;
	int64_t      max_size;
	int64_t      start_offset;
	int64_t      end_offset;
}	            t_dump_params;

void 	display_usage(void);
bool 	parse_argument(const char *argument, t_dump_params *params);
bool 	handle_parameters(t_dump_params *params);
bool 	hexdump(t_dump_params *params);

#endif /* __HEXDUMP_H__ */
