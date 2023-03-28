#include "file.h"
#include <stdio.h>

void file_debug_print(t_file *file)
{
	fprintf(stdout, "t_file: {\n");
	fprintf(stdout, "t_file:     .name='%s'\n", file->name);
	fprintf(stdout, "t_file:     .size=%zu\n", file->size);
	fprintf(stdout, "t_file:     .fd='%d'\n", file->fd);
	fprintf(stdout, "t_file:     .open='%s'\n", (file->open ? "true" : "false"));
	fprintf(stdout, "t_file:     .data\n");
	fprintf(stdout, "t_file:         .mapped='%s'\n", (file->data.mapped ? "true" : "false"));
	fprintf(stdout, "t_file:         .ptr=%p\n", file->data.ptr);
#if defined (__linux__)
	fprintf(stdout, "t_file:         .start=%ld\n", file->data.start);
# else
	fprintf(stdout, "t_file:         .start=%lld\n", file->data.start);
#endif
	fprintf(stdout, "t_file:         .capacity='%zu'\n", file->data.capacity);
	fprintf(stdout, "t_file:  }\n");
}