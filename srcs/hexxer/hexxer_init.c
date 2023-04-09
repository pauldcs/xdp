#include "hexxer.h"
#include "log.h"
#include "file.h"
#include "xtypes.h"
#include "xleaks.h"
#include "file.h"
#include "options/user_options.h"
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

static const char *file_type_lookup[] = {
	"regular file",
	"directory",
	"symlink",
	"socket",
	"pipe",
	"block device",
	"character device",
	"???"
};

static  bool options_within_file_size(t_user_options *opts, size_t file_size)
{   /*
     *Checks that the options provided by the user are not problematic
     */
    if (opts->start_offset < file_size)
	{
        if (opts->start_offset + opts->range > file_size)
        {
            __log__(error,  "range exceeds the maximum offset (%zx)", file_size);
            return (false);
        }
        if (!opts->range)
            opts->range = file_size - opts->start_offset; 
        return (true);
    }

    __log__(error,  
        "start offset (%zx) exceeds the maximum offset (%zx)",
        opts->start_offset,
        file_size
    );
    return (false);
}

static bool file_mmap_from_offset(int fd, t_hexxer *hexxer)
{
	size_t aligned_offset = hexxer->start_offset & ~(sysconf(_SC_PAGE_SIZE) - 1);

	hexxer->start_offset = (hexxer->start_offset - aligned_offset);
	hexxer->data.cap = hexxer->max_size + hexxer->start_offset;
	hexxer->data.size = hexxer->max_size;

	hexxer->data.ptr = mmap(
			NULL,
			hexxer->max_size,
	 		PROT_READ,
	 		MAP_PRIVATE,
	 		fd,
			aligned_offset);
	
	if (hexxer->data.ptr == MAP_FAILED)
	{
		__log__(fatal,  "mmap: %s", strerror(errno));
		return (false);
	}
	hexxer->mapped = true;
	return (true);
}


static bool init_screen(t_file *file, t_hexxer *hexxer)
{   /*
     *     Init a 'screen'. it is used as a buffer to write
	 *     the hexxed data into. This is what is actually 
	 *     written to the console. 
     */
	size_t best_size = file->st.st_blksize / 16 * (16 * 3 + 28) * 8;

	hexxer->screen.ptr = __xmalloc__(best_size);
	if (!hexxer->screen.ptr)
		return (false);
	
	hexxer->screen.size = best_size;
	return (true);
}

static bool init_special_file_hexxer(t_file *file, t_user_options *opts, t_hexxer *hexxer)
{   /*
	 *    If the file is not a regular file and has no size,
	 *    we cannot read it at once so we just note the blksize
	 *    for later reading and allocate a screen.
	 */
	hexxer->start_offset = opts->start_offset;
	hexxer->max_size = opts->range;
	hexxer->data.ptr = __xmalloc__(file->st.st_blksize);
	if (hexxer->data.ptr == NULL)
		return (false);
	hexxer->data.cap = file->st.st_blksize;
	return (true);
}

static bool init_regular_file_hexxer(int fd, t_file *file, t_user_options *opts, t_hexxer *hexxer)
{   /*
	 *     If the file has a known size, we determine if it
	 *     should be mmapped or not. If it is mmappable,
	 *     we mmap it, if not we handle it in the same way as a
	 *     special file, as it must be small in size and we don't
	 *     need to bother optimizing the read.
	 */
	if (!options_within_file_size(opts, file->size))
		return (false);
	
	hexxer->start_offset = opts->start_offset;
	hexxer->max_size = opts->range;

	if (file_mmap_recommended(file, hexxer->max_size))
	{
		if (!file_mmap_from_offset(fd, hexxer))
			return (false);
	} else {
		hexxer->data.ptr = __xmalloc__(file->st.st_blksize);
		if (hexxer->data.ptr == NULL)
			return (false);
		hexxer->data.cap = file->st.st_blksize;
	}
	return (true);
}

t_hexxer *hexxer_init(int fd, t_file *file, t_user_options *opts)
{   /*
	 *     Create a 'hexxer' which is a sort of reader
	 *     only for the purpose of hexdumping.
	 */
	t_hexxer *hexxer = __xmalloc__(sizeof(t_hexxer));
	if (hexxer == NULL) return (NULL);

	bzero(hexxer, sizeof(t_hexxer));
	hexxer->start_offset = opts->start_offset;
	hexxer->max_size = opts->range;

	if (opts->color)
		hexxer->color = true;

	switch (file->type)
	{
		case FILE_TYPE_DIRECTORY:
		case FILE_TYPE_SOCKET:
		case FILE_TYPE_UNKNOWN:
		case FILE_TYPE_SYMBOLIC_LINK:
			__log__(error,
				"%s: Is a %s",
				file->path,
				file_type_lookup[file->type]);
			goto prison;

		case FILE_TYPE_REGULAR:
			if (!init_regular_file_hexxer(fd, file, opts, hexxer))
				goto prison;
			break;

		case FILE_TYPE_PIPE:
		case FILE_TYPE_BLOCK_DEVICE:
		case FILE_TYPE_CHARACTER_DEVICE:
			if (!init_special_file_hexxer(file, opts, hexxer))
				goto prison;
			break;
	}

	if (init_screen(file, hexxer))
		return (hexxer);

prison:
	hexxer_destroy(hexxer);
	__xfree__(hexxer);
	return (NULL);
}