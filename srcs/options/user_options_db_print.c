#include "options/user_options.h"
#include "modes.h" 
#include <stdio.h>

void user_options_db_print(t_user_options *opts)
{
	fprintf(stdout, "t_user_options: {\n");
	fprintf(stdout, "t_user_options:    .filename='%s'\n", opts->filename);
	fprintf(stdout, "t_user_options:    .start_offset=%zu\n", opts->start_offset);
	fprintf(stdout, "t_user_options:    .range=%zu\n", opts->range);
	switch(opts->mode)
	{
		case XDP_REGULAR: fprintf(stdout, "t_user_options:    .mode=REGULAR\n"); break;
		case XDP_STREAM:  fprintf(stdout, "t_user_options:    .mode=STREAM\n"); break; 
		case XDP_STRINGS: fprintf(stdout, "t_user_options:    .mode=STRING\n"); break; 
	}
	fprintf(stdout, "t_user_options: }\n");
}