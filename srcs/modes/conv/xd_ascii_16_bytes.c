#include "xtypes.h"
#include <stdint.h>
#include <stddef.h>

/**
 * Copies up to 16 bytes from the source buffer to the destination buffer,
 * converting each byte to its ASCII representation replacing unprintable
 * characters by '.'
 */
size_t xd_ascii_16_bytes(ut8 *dst, const ut8 *src, size_t n) {
    
    const ut32 *src_u32 = (const ut32*)src;
    ut32       *dst_u32 = (ut32*)dst;

    size_t aligned = n & ~3; // checks the maximum aligned bytes
    size_t     ret = 0;
    
    for (size_t i = 0; i < aligned; i += 4)
    {
        // lookup 4 bytes and write them at once as uint32
        *dst_u32++ =  _PrintByte[*src_u32       & 0xff] \
                    | _PrintByte[*src_u32 >>  8 & 0xff] <<  8 \
                    | _PrintByte[*src_u32 >> 16 & 0xff] << 16 \
                    | _PrintByte[*src_u32 >> 24       ] << 24;
        src_u32++;
        ret += 4;
    }
    if (aligned != n)
    {
        // handles the remaining bytes
        const ut8 *src_unaligned = src + aligned;
        ut8       *dst_unaligned = dst + aligned;
        while (ret < n)
        {
            *dst_unaligned++ = _PrintByte[*src_unaligned++];
            ret++;
        }
    }
    return (ret);
}