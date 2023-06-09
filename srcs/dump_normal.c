#include "hexxer.h"
#include "modes.h"
#include <stdbool.h>

bool dump_normal(t_hexxer *hexxer, t_modes mode)
{
    switch (mode)
    {
        case XDP_REGULAR:
            return (xd_dump_lines(
			        hexxer->data.ptr,
			        hexxer->max_size,
			        hexxer->start_offset,
			        hexxer->screen.ptr,
			        hexxer->screen.size,
                    hexxer->color
                )
            );
        case XDP_STREAM:
            return (xd_dump_hex_stream(
			        hexxer->data.ptr,
			        hexxer->max_size,
			        hexxer->start_offset,
			        hexxer->screen.ptr,
			        hexxer->screen.size
                )
            );
        case XDP_STRINGS:
            return (xd_dump_strings(
			        hexxer->data.ptr,
			        hexxer->max_size,
			        hexxer->screen.ptr,
			        hexxer->screen.size
                )
            );
            
        default:
            break;
    }
    return (false);
}