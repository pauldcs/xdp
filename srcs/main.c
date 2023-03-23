#include "xdp.h"
#include "options.h"
#include <stdlib.h>

int main(int ac, char *av[])
{
	t_user_options *opts = parse_user_options(--ac, ++av);

	if (opts == NULL)
		return (EXIT_FAILURE);
	
	bool success = _entry_(opts);

	return (free(opts), success == false);
}
