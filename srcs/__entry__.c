#include "xdp.h"
#include "log.h"
#include "xtypes.h"
#include "xleaks.h"
#include "options/user_options.h"
#include "hex.h"
#include "file.h"
#include <stdbool.h>

static void clean(int fd, t_file *file, t_hexxer *hexxer)
{
	if (fd) __xclose__(fd);
	hexxer_destroy(hexxer);
	__xfree__(file);
	__xfree__(hexxer);
}

bool __entry__(t_user_options *opts)
{	
	t_file   *file = file_init(opts->filename);
	t_hexxer *hexxer = NULL;

	int fd = 0;
	
	if (file == NULL
		|| !file_open_read(file->path, &fd))
		goto boundless_obscurity;

	hexxer = hexxer_init(fd, file, opts);
	if (hexxer == NULL)
		goto boundless_obscurity;

	file_db_print(file);
	hexxer_db_print(hexxer);

	//hexdump(fd, 0, 0);

	clean(fd, file, hexxer);
 	return (true);

 boundless_obscurity:
 	/* There is still time to find the harmony within."
 	 */
	clean(fd, file, hexxer);
 	return (false);
}
