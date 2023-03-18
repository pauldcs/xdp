#ifndef __HEXDUMP_H__
# define __HEXDUMP_H__

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define END "\e[0m"

# define BASE "0123456789abcdef"

# define report_error(fmt, ...) \
    fputstr(2, "Error: " fmt "\n", ##__VA_ARGS__)

typedef enum e_mode {
	DUMP_CLASSIC,
	DUMP_RAW
}	t_mode;

typedef enum e_map_type {
	MMAP,
	MALLOC
}	t_map_type;

typedef struct s_dump_params {
	t_mode 		 mode;
	bool 		 is_stdin;
	const char   *filename;
	int 		 fd;
	void         *map;
	int          map_type;
	int64_t      actual_size;
	int64_t      max_size;
	int64_t      start_offset;
	int64_t      end_offset;
}	            t_dump_params;

void 	display_usage(void);
bool 	parse_argument(const char *argument, t_dump_params *params);
bool 	prepare_params_struct(t_dump_params *params);
bool 	hexdump(t_dump_params *params);

bool raw_bytes_dump(const void *addr, size_t size);
bool	classic_hexdump_c(const void *addr, size_t n);

#endif /* __HEXDUMP_H__ */
