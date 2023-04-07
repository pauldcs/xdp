#include "xdp.h"
#include "log.h"
#include "xtypes.h"
#include "xleaks.h"
#include "modes.h"
#include "options/user_options.h"
#include "hexxer.h"
#include "file.h"
#include <stdbool.h>
#include <unistd.h>

static void clean(int fd, t_file *file, t_hexxer *hexxer);

bool __entry__(t_user_options *opts, cstr_t filename)
{	
	t_file *file = file_init(filename);
	t_hexxer *hexxer = NULL;
	int fd = 0;
	
	if (file == NULL
		|| !file_open_read(file->path, &fd))
		goto forbidden_land;

	hexxer = hexxer_init(fd, file, opts);
	if (hexxer == NULL)
		goto forbidden_land;

#if 0
	/* This prints the 3 main structs
	 *  user options
	 *  the file
	 *  the appropriate hexxer
	*/
	user_options_db_print(opts);
	file_db_print(file);
	hexxer_db_print(hexxer);
#endif	
	if (hexxer->mapped)
		(void)dump_normal(hexxer, opts->mode);
	else
		(void)dump_live(fd, hexxer, opts->mode);
	
	write(1,"\n",1);
	clean(fd, file, hexxer);
 	return (true);

 forbidden_land:
 	/* 𝔗𝔥𝔢𝔯𝔢 𝔦𝔰 𝔰𝔱𝔦𝔩𝔩 𝔱𝔦𝔪𝔢 𝔱𝔬 𝔣𝔦𝔫𝔡 𝔱𝔥𝔢 𝔥𝔞𝔯𝔪𝔬𝔫𝔶 𝔴𝔦𝔱𝔥𝔦𝔫
	 */
	clean(fd, file, hexxer);
 	return (false);
}

static void clean(int fd, t_file *file, t_hexxer *hexxer)
{
	if (fd) __xclose__(fd);
	hexxer_destroy(hexxer);
	__xfree__(file);
	__xfree__(hexxer);
}
