#ifndef __HEXDUMP_H__
# define __HEXDUMP_H__

# include "libstringf.h"
# include <errno.h>
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

typedef struct s_dump_params {
	t_mode 		 mode;
	bool 		 is_stdin;
	const char   *filename;
	int 		 fd;
	void         *data;
	bool 		 is_mapped;
	int64_t      capacity;
	int64_t      file_size;
	int64_t      range_size;
	int64_t      aligned_offset;
	int64_t      start_offset;
	int64_t      end_offset;
}	            t_dump_params;

void 	__usage(void);
char 	*get_next_argument(int *ac, char ***av);
void 	debug_params(t_dump_params *params);
bool 	safe_open(t_dump_params *params);
bool	should_use_mmap(int fd, size_t file_size, size_t range_size);
bool 	memory_efficient_mmap(t_dump_params *params);
bool 	read_range_only(t_dump_params *params);
bool 	try_parse_argument(const char *argument, t_dump_params *params);
bool 	read_data_from_stdin(t_dump_params *params);
bool 	build_dump_structure(t_dump_params *params);
bool 	hexdump(t_dump_params *params);

bool 	raw_bytes_dump(const void *addr, size_t size);
bool	classic_hexdump_c(const void *addr, size_t n);

#endif /* __HEXDUMP_H__ */
