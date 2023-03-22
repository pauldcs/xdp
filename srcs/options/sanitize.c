#include "hdump.h"
#include "logging.h"
#include <stdbool.h>

/* Builds a dump structure based on the input parameters,
 * verifying and adjusting the range if needed.
 */
bool sanitize(t_hd_opts *opts)
{
    if (opts->file.data.start < opts->file.size) {
        if (opts->file.data.start + opts->file.data.range > opts->file.size) {
            
            LOG(WARNING, 
                "range exceeds the maximum offset (%p), trucating it to %d",
                    opts->file.size,
                    opts->file.size - opts->file.data.start
            );
            
            opts->file.data.range = opts->file.size - opts->file.data.start;
        }
        if (!opts->file.data.range)
            opts->file.data.range = opts->file.size - opts->file.data.start;  
        
        return (true);
    }
    
    FATAL_ERROR(
        "start offset (%p) exceeds the maximum offset (%p)",
            opts->file.data.start,
            opts->file.size
    );

    return (false);
}
