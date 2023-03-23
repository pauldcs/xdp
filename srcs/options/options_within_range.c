#include "xdp.h"
#include "debug/logging.h"
#include "options.h"
#include <stdbool.h>

bool options_within_range(t_user_options *opts, t_infile *file)
{
    if (opts->start_offset < file->size) {
        if (opts->start_offset + opts->range > file->size)
        {
            FATAL_ERROR("range exceeds the maximum offset (%x)", file->size);
            return (false);
        }
        if (!opts->range)
            opts->range = file->size - opts->start_offset; 
        return (true);
    }

    FATAL_ERROR(
        "start offset (%p) exceeds the maximum offset (%p)",
        opts->start_offset,
        file->size
    );
    return (false);
}
