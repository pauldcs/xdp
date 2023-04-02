#include "hex.h"
#include "log.h"
#include <stdio.h>

void hexxer_db_print(t_hexxer *hexxer)
{
	fprintf(stdout, "t_hexxer: {\n");
	fprintf(stdout, "t_hexxer:     .max_size=%zu\n", hexxer->max_size);
	fprintf(stdout, "t_hexxer:     .start_offset=%zu\n", hexxer->start_offset);
	fprintf(stdout, "t_hexxer:     .mapped=%s\n", (hexxer->mapped ? "true":"false"));
	fprintf(stdout, "t_hexxer:     .screen\n");
	fprintf(stdout, "t_hexxer:         .ptr=%p\n", hexxer->screen.ptr);
	fprintf(stdout, "t_hexxer:         .size=%zu\n", hexxer->screen.size);
	fprintf(stdout, "t_hexxer:     .data\n");
	fprintf(stdout, "t_hexxer:         .ptr=%p\n", hexxer->data.ptr);
	fprintf(stdout, "t_hexxer:         .size=%zu\n", hexxer->data.size);
	fprintf(stdout, "t_hexxer:         .cap=%zu\n", hexxer->data.cap);
	fprintf(stdout, "t_hexxer: }\n");
}