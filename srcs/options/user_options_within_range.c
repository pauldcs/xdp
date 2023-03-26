#include "xdp.h"
#include "log.h"
#include "options/user_options.h"
#include <stdbool.h>

bool user_options_within_range(t_user_options *opts, size_t file_size)
{
    if (opts->start_offset < file_size) {
        if (opts->start_offset + opts->range > file_size)
        {
            log_message(fatal,  "range exceeds the maximum offset (%zx)", file_size);
            return (false);
        }
        if (!opts->range)
            opts->range = file_size - opts->start_offset; 
        return (true);
    }

    log_message(fatal,  
        "start offset (%zx) exceeds the maximum offset (%zx)",
        opts->start_offset,
        file_size
    );
    return (false);
}
