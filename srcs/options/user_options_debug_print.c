#include "options/user_options.h"
#include <stdio.h>

void user_options_debug_print(t_user_options *opts)
{
	fprintf(stdout, "t_user_options: {\n");
	fprintf(stdout, "t_user_options:    .filename='%s'\n", opts->filename);
	fprintf(stdout, "t_user_options:    .start_offset=%zu\n", opts->start_offset);
	fprintf(stdout, "t_user_options:    .string_size=%zu\n", opts->string_size);
	fprintf(stdout, "t_user_options:    .colors=%d\n", opts->colors);
	fprintf(stdout, "t_user_options:    .range=%zu\n", opts->range);
	fprintf(stdout, "t_user_options:    .mode=%d\n", opts->mode);
	fprintf(stdout, "t_user_options: }\n");
}