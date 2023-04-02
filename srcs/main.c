#include "xdp.h"
#include "log.h"
#include "xleaks.h"
#include "options/user_options.h"
#include <stdlib.h>

int main(int ac, char *av[])
{	
	t_user_options *opts = user_options_parse(ac, av);

	if (opts == NULL)
		return (EXIT_FAILURE);
	
	bool success = __entry__(opts);
	
	int ret = success == false;

	__xfree__(opts);

	return (ret);
}
