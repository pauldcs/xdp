#ifndef __MODES_H__
# define __MODES_H__

# include "xtypes.h"
# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

typedef enum e_modes {
    XDP_REGULAR,
    XDP_STREAM,
    XDP_STRINGS
}   t_modes;

ssize_t	xd_dump_lines(const ut8 *addr, size_t n, size_t offset, ut8 *scr_ptr, size_t scr_size);
bool string_dump(const uint8_t* addr, size_t n, size_t len);
bool xd_dump_hex_stream(cut8 *addr, size_t size, size_t offset, ut8 *scr_ptr, size_t scr_size);

#endif