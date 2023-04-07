#include "hexxer.h"
#include "xtypes.h"
#include <stdint.h>
#include <stddef.h>

size_t xd_pointer_8_bytes(ut8 *dst, uintptr_t p) {
    static const char hex_chars[] = "0123456789abcdef";
    for (int i = 7; i >= 0; --i) {
        dst[i] = hex_chars[p & 0xf];
        p >>= 4;
    }
    return (8);
}	