#ifndef __FILE_H__
# define __FILE_H__

# include <stddef.h>

typedef struct s_hd_file_data
	{
		void *ptr;
		size_t start;
		size_t range;
		size_t bufsize;
	}   t_hd_file_data;

typedef struct s_hd_file
{
	const char *name;
	size_t size;
	int fd;
	t_hd_file_data data;
}   t_hd_file;

bool 	file_try_open(t_hd_file *file);
bool    file_mmap_recommended(t_hd_file *file);
bool 	file_mmap_from_offset(t_hd_file *file);
bool 	file_read_from_offset(t_hd_file *file);

#endif /* __FILE_H__ */