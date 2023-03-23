#include "infile.h"
#include "libs/libstringf.h"

void infile_struct_debug_print(t_infile *file)
{
	putstr("t_infile: {\n");
	putstr("t_infile:     .name='%s'\n", file->name);
	putstr("t_infile:     .size=%d\n", file->size);
	putstr("t_infile:     .fd='%d'\n", file->fd);
	putstr("t_infile:     .open='%s'\n", (file->open ? "true" : "false"));
	putstr("t_infile:     .data\n");
	putstr("t_infile:         .mapped='%s'\n", (file->data.mapped ? "true" : "false"));
	putstr("t_infile:         .ptr=%p\n", file->data.ptr);
	putstr("t_infile:         .start=%d\n", file->data.start);
	putstr("t_infile:         .capacity='%d'\n", file->data.capacity);
	putstr("t_infile:  }\n");
}