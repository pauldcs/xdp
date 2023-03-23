#ifndef __FILE_H__
# define __FILE_H__

# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>
# include <stdint.h>

typedef struct s_infile
{
	const char   *name;
	size_t       size;
	int          fd;
	bool         open;
	bool         eof;
	struct s_data
	{
		bool     mapped;
		void     *ptr;
		off_t    start;
		size_t   size;
		size_t   capacity;
	} data;
} t_infile;

void infile_struct_debug_print(t_infile *file);
bool infile_get_size(t_infile *file);
bool infile_open(t_infile *file);
void infile_close(t_infile *file);
bool infile_mmap_recommended(t_infile *file, size_t range_size);
bool infile_mmap_from_offset(t_infile *file, size_t range_size);
bool infile_read_from_offset(t_infile *file, size_t range, off_t start_offset);
void infile_destroy(t_infile *file);

#endif /* __FILE_H__ */