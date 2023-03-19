#include "hexdump.h"
#include "logging.h"
#include <stdbool.h>

bool build_dump_structure(t_dump_params *params)
{
    if (params->start_offset < params->file_size) {
        if (params->start_offset + params->range_size > params->file_size) {
            
            LOG(WARNING, 
                "range exceeds the maximum offset (%p), trucating it to %d",
                params->file_size,
                params->file_size - params->start_offset
            );
            
            params->range_size = params->file_size - params->start_offset;
        }
        if (!params->range_size) {
            params->range_size = params->file_size - params->start_offset;
            
            LOG(DEBUG, 
                "range size: %db",
                params->file_size - params->start_offset
            );
        }
        
        LOG(DEBUG, 
            "%s: ok to dump from address %p",
            __func__,
            params->start_offset
        );

        return (true);
    }
    LOG(FATAL, 
        "start offset (%p) exceeds the maximum offset (%p)",
        params->start_offset,
        params->file_size
    );
    return (false);
}
