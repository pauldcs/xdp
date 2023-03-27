#ifndef __FILE_H__
# define __FILE_H__

# include "xtypes.h"
# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>
# include <stdint.h>

/**
 * @brief Internal representation of a file
 * 
 */
typedef struct s_file
{
	const char   *name; /* orgiginal name */
	size_t       size;  /* file size in bytes */
	bool         open;  /* true if the file is currently open */
	int          fd;    /* the fd of the file */
	struct s_data
	{
		bool     mapped;   /* true if the file is mmaped*/
		void     *ptr;     /* the ptr to the data block */
		off_t    start;    /* the start of the actual data */
		size_t   size;     /* the size of the actual data */
		size_t   capacity; /* the size of the whole block */
	} data;
} t_file;

/**
 * @brief This function creates a `t_file` from a filename.
 * 
 * The function tries to open `filename` for read only.
 * On success a new allocated t_file is returned and the
 * `open` field is set to true. Otherwise NULL.
 * 
 * @param filename the name of the file to load
 * 
 * @return t_file* (must be freed)
 */
t_file *load_user_file(ct8 *filename);

/**
 * @brief Initializes an empty t_file with the name and size of the file.
 * 
 * This function checks that the given filename is a valid
 * file. If it is valid the `size` and the `name` fields 
 * are set and true is returned.
 * 
 * @param filename The name of the file to initialize
 * @param file the empty t_file
 * 
 * @return bool 
 */
bool file_init(const char *filename, t_file *file);
void file_destroy(t_file *file);

/*-- File status --*/
bool file_exists(const char *filename);
bool file_get_size(const char *filename, size_t *size);
bool file_is_directory(const char *filename);
bool file_is_regular(const char *filename);

/*-- File manip --*/
bool file_open_read(const char *filename, int *fd);
bool file_open_write(const char *filename, int *fd);
bool file_open_append(const char *filename, int *fd);

/*-- Other --*/
void file_debug_print(t_file *file);
bool file_mmap_recommended(t_file *file, size_t range_size);
bool file_mmap_from_offset(t_file *file, size_t range_size);

/*-- File descriptor status --*/
bool fd_is_valid(int fd);
bool fd_is_writable(int fd);
bool fd_is_socket(int fd);
bool fd_is_regular(int fd);
bool fd_is_readable(int fd);
bool fd_is_pipe (int fd);
bool is_directory(int fd);
bool fd_is_character_device(int fd);
bool fd_is_block_device(int fd);

#endif /* __FILE_H__ */