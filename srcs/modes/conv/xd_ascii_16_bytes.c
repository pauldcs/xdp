#include "xtypes.h"
#include <stdint.h>
#include <stddef.h>

/* Writes 16 bytes of ascii into __screen__, non printable characters
 * are replaced by '.'
 */
size_t xd_ascii_16_bytes(ut8 *dst, cut8 *src, size_t n) {
    size_t ret = 0;
    if (n == 16) {
        for (size_t i = 0; i < 16; i++)
            dst[i] = _PrintByte[src[i]];
        return 16;
    }
    while (n--)
        dst[ret++] = _PrintByte[*src++];
    return ret;
}