#ifndef __HEXDUMP_H__
# define __HEXDUMP_H__

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

# define BASE "0123456789abcdef"

//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define END "\e[0m"
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

#define report_error(fmt, ...) \
    fputstr(2, "Error: " fmt "\n", ##__VA_ARGS__)

void 	display_usage(void);
bool 	parse_argument(const char *argument, t_dump_params *params);
bool 	handle_parameters(t_dump_params *params);
bool 	hexdump(t_dump_params *params);

#endif /* __HEXDUMP_H__ */
