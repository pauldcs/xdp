#ifndef __HEX_H__
# define __HEX_H__

# include "xtypes.h"
# include "file.h"
# include "options/user_options.h"
# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

	/*-- Convert --*/
size_t	xd_ascii_16_bytes(ut8 *dst, const ut8 *src, size_t n);
size_t	xd_data_16_bytes(cut8 *dst, cut8 *src, size_t n);
size_t	xd_pointer_8_bytes(ut8 *dst, const uintptr_t p);
size_t	xd_pointer_p8_bytes(ut8 *dst, const uintptr_t p);

typedef struct s_hexxer {
	size_t max_size;     /* if > 0: should be used as the size of the file */
	size_t start_offset; /* where to start reading the file */
	bool mapped;         /* the file is mmapped */
	struct s_screen {
		ptr_t ptr;       /* pointer to the screen */
		size_t size;     /* the size of the screen */
	} screen;
	union {
		struct s_data {
			ptr_t ptr;   /* pointer to `start_offset` in the file */
			size_t size; /* the size of the data */
			size_t cap;  /* the size of the allocated memory */
		} data;
	};
}	t_hexxer;

t_hexxer *hexxer_init(int fd, t_file *file, t_user_options *opts);
void hexxer_destroy(t_hexxer *hexxer);
void hexxer_db_print(t_hexxer *hexxer);

#endif /* __HEX_H__ */