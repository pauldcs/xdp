#include "options/user_options.h"
#include <string.h>

void user_options_init(t_user_options *opts)
{
	memset(opts, 0x00, sizeof(t_user_options));
	return ;
}