#include "hex.h"
#include "xleaks.h"
#include "xtypes.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/* Forces to write the buffer fully if write() failes, 
 * it's ok if this ends up looping endlessly.
 */
static size_t	write_all(int fd, const void *buf, size_t s)
{
	ssize_t	c;
	size_t	ret;

	ret = 0;
	while (s)
	{
		c = write(fd, buf + ret, s);
		if (c == -1)
			break ;
		ret += c;
		s -= c;
	}
	return (ret);
}

inline size_t	xd_pointer_p8_bytes(ut8 *dst, const uintptr_t p)
{
	uintptr_t 	ptr = (uintptr_t)p;
	cut8 		abc = "0123456789abcdef"

	*(dst + 8) = abc[(ptr >>  0) & 0xf];
	*(dst + 7) = abc[(ptr >>  4) & 0xf];
	*(dst + 6) = abc[(ptr >>  8) & 0xf];
	*(dst + 5) = abc[(ptr >> 12) & 0xf];
	*(dst + 4) = abc[(ptr >> 16) & 0xf];
	*(dst + 3) = abc[(ptr >> 20) & 0xf];
	*(dst + 2) = abc[(ptr >> 24) & 0xf];
	*(dst + 1) = abc[(ptr >> 28) & 0xf];
	*(dst + 0) = '0';

	/* add '+' to the hex number */
	int i = 0;
	while ((ptr >>= 4))
		i++;
	*(dst + 7 - i) = '+';
	return (9);
}

inline size_t xd_data_16_bytes(cut8 *dst, cut8 *src, size_t n)
{
	if (n >= 16) {
		/*-- 0 - 8 --*/
			*(ut16 *)(dst +  0) = _B16Pair[*(src + 0)];
			*(ut16 *)(dst +  3) = _B16Pair[*(src + 1)];
			*(ut16 *)(dst +  6) = _B16Pair[*(src + 2)];
			*(ut16 *)(dst +  9) = _B16Pair[*(src + 3)];
			*(ut16 *)(dst + 12) = _B16Pair[*(src + 4)];
			*(ut16 *)(dst + 15) = _B16Pair[*(src + 5)];
			*(ut16 *)(dst + 18) = _B16Pair[*(src + 6)];
			*(ut16 *)(dst + 21) = _B16Pair[*(src + 7)];
		/*-- 8 - 16 --*/
			*(ut16 *)(dst + 24) = _B16Pair[*(src +  8)];
			*(ut16 *)(dst + 27) = _B16Pair[*(src +  9)];
			*(ut16 *)(dst + 30) = _B16Pair[*(src + 10)];
			*(ut16 *)(dst + 33) = _B16Pair[*(src + 11)];
			*(ut16 *)(dst + 36) = _B16Pair[*(src + 12)];
			*(ut16 *)(dst + 39) = _B16Pair[*(src + 13)];
			*(ut16 *)(dst + 42) = _B16Pair[*(src + 14)];
			*(ut16 *)(dst + 45) = _B16Pair[*(src + 15)];
		/*------------*/
		return (47);

	} else {

		ut8 	*ptr = (ut8 *)src;
		cut8 	*tmp = dst;
		ut64 	pad = (16 - n) * 3;

		if (pad)
			pad--;
	
		while (n--) {
			*(ut16 *)(dst) = _B16Pair[*ptr++];
			dst += 3;
		}
		return (dst - tmp + pad);
	}
	return (0);
}

/* Writes 16 bytes of ascii into __screen__, non printable characters
 * are replaced by '.'
 */
inline size_t	xd_ascii_16_bytes(ut8 *dst, cut8 *src, size_t n)
{
	size_t ret = 0;

	if (n >= 16) {
		/*-- 0 - 8 --*/
			dst[0] = _PrintByte[*(src + 0)];
			dst[1] = _PrintByte[*(src + 1)];
			dst[2] = _PrintByte[*(src + 2)];
			dst[3] = _PrintByte[*(src + 3)];
			dst[4] = _PrintByte[*(src + 4)];
			dst[5] = _PrintByte[*(src + 5)];
			dst[6] = _PrintByte[*(src + 6)];
			dst[7] = _PrintByte[*(src + 7)];
		/*-- 8 - 16 --*/
			dst[8]  = _PrintByte[*(src +  8)];
			dst[9]  = _PrintByte[*(src +  9)];
			dst[10] = _PrintByte[*(src + 10)];
			dst[11] = _PrintByte[*(src + 11)];
			dst[12] = _PrintByte[*(src + 12)];
			dst[13] = _PrintByte[*(src + 13)];
			dst[14] = _PrintByte[*(src + 14)];
			dst[15] = _PrintByte[*(src + 15)];
		/*------------*/
		return (16);
	
	} else {
		ut8 *tmp = (ut8 *)src;
		while (n--)
			dst[ret++] = _PrintByte[*tmp++];
	}
	return (ret);
}

bool	xd_dump_lines(const uint8_t *addr, size_t size, size_t offset)
{
	uint8_t     *prev = NULL;
	uint8_t     *ptr = (uint8_t *)addr;
	uint8_t     *__scr_ptr = NULL;
	size_t      __scr_off = 0;

	__scr_ptr = __xmalloc__(SCREEN_BUFFER_SIZE + 32);
	if (!__scr_ptr)
		return (false);

	memset(__scr_ptr, ' ', SCREEN_BUFFER_SIZE);

	bool dump_required = false;
	size_t line_size;

	while (size) {	

		if (dump_required) {
			write_all(
				STDOUT_FILENO,
				__scr_ptr,
				__scr_off);
			__scr_off = 0;
			dump_required = false;
		}

		if (size < 16) {
			line_size = size;
			size = 0;
		
		} else {
			if (prev) {
				if (*(uint64_t *)(    prev) == *(uint64_t *)(    ptr) && 
					*(uint64_t *)(prev + 8) == *(uint64_t *)(ptr + 8)) {
					if (__scr_off) {
						*(__scr_ptr + __scr_off++) = '+';
						*(__scr_ptr + __scr_off++) = '\n';
						dump_required = true;
					} 
					offset += 16;
					ptr += 16;
					size -= 16;
					continue;
				}
			}
			line_size = 16;
			size -= 16;
		}

		__scr_off += xd_pointer_p8_bytes(__scr_ptr + __scr_off, offset) + 2;
		__scr_off += xd_data_16_bytes(__scr_ptr + __scr_off, ptr, line_size) + 2;
		__scr_off += xd_ascii_16_bytes(__scr_ptr + __scr_off, ptr, line_size);
		*(__scr_ptr + __scr_off++) = '\n';

		if (__scr_off >= SCREEN_BUFFER_SIZE)
			dump_required = true;

		prev = ptr;
		offset += 16;
		ptr += 16;
	}	

	if (__scr_off)
		write_all(STDOUT_FILENO, __scr_ptr, __scr_off);
	
	return(__xfree__(__scr_ptr), true);
}