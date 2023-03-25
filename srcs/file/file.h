#ifndef __FILE_H__
# define __FILE_H__

# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>
# include <stdint.h>

typedef struct s_file
{
	const char   *name;
	size_t       size;
	bool         open;
	int          fd;
	struct s_data
	{
		bool     mapped;
		void     *ptr;
		off_t    start;
		size_t   size;
		size_t   capacity;
	} data;
} t_file;

bool file_open_read(const char *filename, int *fd);
bool file_open_write(const char *filename, int *fd);
bool file_open_append(const char *filename, int *fd);

bool file_init(const char *filename, t_file *file);
void file_destroy(t_file *file);

bool file_exists(const char *filename);
bool file_get_size(const char *filename, size_t *size);


void file_debug_print(t_file *file);
bool file_mmap_recommended(t_file *file, size_t range_size);
bool file_mmap_from_offset(t_file *file, size_t range_size);
bool file_read_from_offset(t_file *file, size_t range, off_t start_offset);
void file_destroy(t_file *file);

#endif /* __FILE_H__ */