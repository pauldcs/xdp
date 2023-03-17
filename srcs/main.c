#include "hexdump.h"
#include <stdlib.h>
#include <string.h>

static const char *get_next_argument(int *ac, char ***av)
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

	if (ac < 2) {
		display_usage();
		return (EXIT_FAILURE);
	}
	memset(&params, 0, sizeof(params));
	while ((ptr = (char *)get_next_argument(&ac, &av))) {
		if (!parse_argument(ptr, &params))
			return (EXIT_FAILURE);
	}
	if (hexdump(&params))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
