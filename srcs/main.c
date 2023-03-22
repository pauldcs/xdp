#include "hdump.h"
#include "logging.h"
#include "options.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int ac, char *av[])
{
	t_hd_opts 	opts;
	char		*ptr;
	int         ret;

	LOG(WARNING, "Debug mode is enabled");
	
	memset(&opts, 0, sizeof(opts));
	while ((ptr = get_next_argument(&ac, &av))) {
		if (!parse_single_option(ptr, &opts, &ac, &av))
			return (EXIT_FAILURE);
	}

	if (!opts.file.name)
		return (usage(), EXIT_SUCCESS);
	ret = !_entry_(&opts);
	if (opts.file.fd > 0)
		close(opts.file.fd);
	return (ret);
}
