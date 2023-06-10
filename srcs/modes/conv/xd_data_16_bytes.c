#include "xtypes.h"
#include "xdp.h"
#include "hexxer.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

static const char padding[] = {
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', 
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', 
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', 
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', 
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', 
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', 
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', 
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' 
};

size_t xd_data_16_bytes(cut8 *dst, cut8 *src, size_t n)
{	
    switch (n) {
		/* 
		 *     almost always 16 so handling each size
		 *     might be a waste of time
		 */
	case 16:
		for (size_t i = 0; i < n; i += 2, dst += 6) {
			*(ut32 *)(dst)     = _B16PairSpaced[src[i]];
			*(ut32 *)(dst + 3) = _B16PairSpaced[src[i+1]];
		}		
		return (47);

    default: 
		for (size_t i = 0; i < n; i++, dst += 3) {
        	*(ut32 *)(dst) = _B16PairSpaced[src[i]];
		}
	}
	__builtin_memcpy((void *)dst, padding, (16 - n) * 3);
    return (47);
}