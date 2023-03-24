#include "infile.h"
#include <stdio.h>

void infile_struct_debug_print(t_infile *file)
{
	fprintf(stdout, "t_infile: {\n");
	fprintf(stdout, "t_infile:     .name='%s'\n", file->name);
	fprintf(stdout, "t_infile:     .size=%zu\n", file->size);
	fprintf(stdout, "t_infile:     .fd='%d'\n", file->fd);
	fprintf(stdout, "t_infile:     .open='%s'\n", (file->open ? "true" : "false"));
	fprintf(stdout, "t_infile:     .data\n");
	fprintf(stdout, "t_infile:         .mapped='%s'\n", (file->data.mapped ? "true" : "false"));
	fprintf(stdout, "t_infile:         .ptr=%p\n", file->data.ptr);
	fprintf(stdout, "t_infile:         .start=%lld\n", file->data.start);
	fprintf(stdout, "t_infile:         .capacity='%zu'\n", file->data.capacity);
	fprintf(stdout, "t_infile:  }\n");
}