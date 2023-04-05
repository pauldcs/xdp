#ifndef __FILE_H__
# define __FILE_H__

# include "xtypes.h"
# include <stddef.h>
# include <stdbool.h>
# include <sys/stat.h>

typedef enum e_file_type {
    FILE_TYPE_REGULAR,
    FILE_TYPE_DIRECTORY,
    FILE_TYPE_SYMBOLIC_LINK,
    FILE_TYPE_SOCKET,
    FILE_TYPE_PIPE,
    FILE_TYPE_BLOCK_DEVICE,
    FILE_TYPE_CHARACTER_DEVICE,
    FILE_TYPE_UNKNOWN
} t_file_type;

typedef struct s_file {
	t_file_type type;
	cstr_t path;
	size_t size;
	struct stat st;
} t_file;

// typedef struct s_file_data {
//     t_file source;
//     struct s_slice {
//         ptr_t ptr;
//         size_t size;
//         ptr_t it_begin;
//         ptr_t it_end;
//     } slice;
// }   t_file_data;


t_file   *file_init(ct8 *filename);
void      file_db_print(t_file *file);

bool file_mmap_recommended(t_file *file, size_t range_size);

bool file_open_read(const char *filename, int *fd);
bool file_open_append(const char *filename, int *fd);
bool file_open_write(const char *filename, int *fd);


#endif /* __FILE_H__ */