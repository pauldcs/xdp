#include "xdp.h"
#include "debug/logging.h"
#include "options.h"
#include <stdbool.h>

bool options_within_range(t_user_options *opts, t_file *file)
{
    if (opts->start_offset < file->size) {
        if (opts->start_offset + opts->range > file->size)
        {
            FATAL_ERROR("range exceeds the maximum offset (%zx)", file->size);
            return (false);
        }
        if (!opts->range)
            opts->range = file->size - opts->start_offset; 
        return (true);
    }

    FATAL_ERROR(
        "start offset (%zx) exceeds the maximum offset (%zx)",
        opts->start_offset,
        file->size
    );
    return (false);
}
