#include "hexdump.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int ac, char *av[])
{
	t_dump_params 	params;
	char			*ptr;
	int             ret;

	memset(&params, 0, sizeof(params));
	while ((ptr = get_next_argument(&ac, &av))) {
		if (!try_parse_argument(ptr, &params, &ac, &av))
			return (EXIT_FAILURE);
	}
	ret = !dump(&params);
	if (params.file.fd)
		close(params.file.fd);
	return (ret);
}
