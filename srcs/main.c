#include "hexdump.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static char *get_next_argument(int *ac, char ***av)
{
	if (*ac) {
		--(*ac);
		return (*++*av);
	}
	return (NULL);
}

int main(int ac, char *av[])
{
	t_dump_params 	params;
	char			*ptr;
	int             ret;

	memset(&params, 0x00, sizeof(params));
	while ((ptr = get_next_argument(&ac, &av)) != NULL) {
		if (!parse_single_argument(ptr, &params))
			return (EXIT_FAILURE);
	}
	ret = hexdump(&params);
	if (params.fd)
		close(params.fd);
	return (ret);
}
