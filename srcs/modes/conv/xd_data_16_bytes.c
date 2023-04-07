#include "xtypes.h"
#include "xdp.h"
#include "hexxer.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

static const size_t padding_table[] = { 15, 14, 12, 13, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7 };

size_t xd_data_16_bytes(cut8 *dst, cut8 *src, size_t n)
{	
    switch (n) {
	case 16:
		for (size_t i = 0; i < n; i += 2, dst += 6) {
			*(ut16 *)(dst)     = _B16Pair[src[i]];
			*(ut16 *)(dst + 3) = _B16Pair[src[i+1]];
		}		
		return (47);
		
	// case 15:
	// case 14:
	// case 13:
	// case 12:
	// case 11:
	// case 10:
	// case 9: 
	// case 8: 
	// case 7: 
	// case 6: 
	// case 5: 
	// case 4: 
	// case 3: 
	// case 2: 
	// case 1: 

    default: 
		break;
	}
	size_t padding = padding_table[n-1];
	__builtin_memset((void *)(dst + (16 - padding) * 3), ' ', padding * 3);

    for (size_t i = 0; i < n; i++, dst += 3)
        *(ut16 *)(dst) = _B16Pair[src[i]];

    return (47);
}