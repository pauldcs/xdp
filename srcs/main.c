#include "xdp.h"
#include "debug/logging.h"
#include "options.h"
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char *av[])
{
	__log(Warning, "Debug mode is enabled");

	t_user_options *opts = parse_user_options(--ac, ++av);

	if (opts == NULL)
		return (EXIT_FAILURE);
	
	bool success = _entry_(opts);

	return (free(opts), success == false);
}
