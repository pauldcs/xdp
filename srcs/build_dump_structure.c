#include "hdump.h"
#include "logging.h"
#include <stdbool.h>

/* Builds a dump structure based on the input parameters,
 * verifying and adjusting the range if needed.
 */
bool build_dump_structure(t_dump_params *params)
{
    if (params->file.start_offset < params->file.file_size) {
        if (params->file.start_offset + params->file.range_size > params->file.file_size) {
            
            LOG(WARNING, 
                "range exceeds the maximum offset (%p), trucating it to %d",
                params->file.file_size,
                params->file.file_size - params->file.start_offset
            );
            
            params->file.range_size = params->file.file_size - params->file.start_offset;
        }
        if (!params->file.range_size)
            params->file.range_size = params->file.file_size - params->file.start_offset;   

        LOG(DEBUG, 
            "range size: %db",
            params->file.file_size - params->file.start_offset
        ); 
        
        return (true);
    }
    
    FATAL_ERROR(
        "start offset (%p) exceeds the maximum offset (%p)",
        params->file.start_offset,
        params->file.file_size
    );

    return (false);
}
