#include "hexxer.h"
#include "modes.h"
#include <stdbool.h>

bool dump_normal(t_hexxer *hexxer, t_modes mode)
{
    (void)mode;
    return (xd_dump_lines(
			hexxer->data.ptr,
			hexxer->max_size,
			hexxer->start_offset,
			hexxer->screen.ptr,
			hexxer->screen.size
		));
}