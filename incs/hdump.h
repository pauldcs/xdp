#ifndef __HDUMP_H__
# define __HDUMP_H__

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
# define GRY "\x1b[2;37m"
# define END "\e[0m"

#define BLK_UINT64 *(uint64_t*)BLK
#define RED_UINT64 *(uint64_t*)RED
#define GRN_UINT64 *(uint64_t*)GRN
#define YEL_UINT64 *(uint64_t*)YEL
#define BLU_UINT64 *(uint64_t*)BLU
#define MAG_UINT64 *(uint64_t*)MAG
#define CYN_UINT64 *(uint64_t*)CYN
#define WHT_UINT64 *(uint64_t*)WHT
#define GRY_UINT64 *(uint64_t*)GRY
#define END_UINT64 *(uint64_t*)END

# define BASE16_ASCII_CHARS "0123456789abcdef"

# define report_error(fmt, ...) \
    fputstr(2, "hdump: " fmt "\n", ##__VA_ARGS__)

typedef enum e_mode {
	DUMP_CLASSIC,
	DUMP_STRINGS,
	DUMP_RAW
}	t_mode;

typedef struct s_dump_params {
	t_mode 	mode;
	size_t  string_size;
	bool 	colored_output;
	struct  s_data {
		void         *data;
		bool 		 is_mapped;
		size_t       aligned_offset;
		size_t       capacity;
	}   data;
	struct  s_file {
		const char   *filename;
		int 		 fd;
		size_t       file_size;
		size_t       range_size;
		size_t       start_offset;
	}   file;
}	t_dump_params;

char 	*get_next_argument(int *ac, char ***av);
bool 	_entry(t_dump_params *params);
bool	perform_string_dump(const uint8_t *addr, size_t n, size_t len);
bool 	perform_raw_hexdump(const void *addr, size_t size);
bool	perform_regular_hexdump(const void *addr, size_t n, size_t start_offset);
bool	perform_color_hexdump(const void *addr, size_t n, size_t start_offset);
void 	__usage(void);

#endif /* __HEXDUMP_H__ */
