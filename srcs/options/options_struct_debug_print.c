#include "options.h"
#include "libs/libstringf.h"

void options_struct_debug_print(t_user_options *opts)
{
	putstr("t_user_options: {\n");
	putstr("t_user_options:    .filename='%s'\n", opts->filename);
	putstr("t_user_options:    .start_offset=%d\n", opts->start_offset);
	putstr("t_user_options:    .range=%d\n", opts->range);
	putstr("t_user_options:    .mode=%d\n", opts->mode);
	putstr("t_user_options: }\n");
}