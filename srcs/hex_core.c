#include "hdump.h"
#include "utils.h"
#include "xlookup.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

static uint8_t *__screen__;
static size_t   __screen_offset__ = 0;

/* Dumps the content of __screen__ to stdout
 */
static void __dump_screen(void)
{
	write_all(STDOUT_FILENO,
		__screen__,
		__screen_offset__);
	__screen_offset__ = 0;
}

/* Writes a offset in hex format into __screen__
 */
static inline void	write_offset(const uintptr_t p)
{
	uint8_t		*buffer = (uint8_t *)(__screen__ + __screen_offset__);
	uintptr_t ptr = (uintptr_t)p;

	*(buffer + 7) = BASE16_ASCII_CHARS[(ptr >>  0) & 0xf];
	*(buffer + 6) = BASE16_ASCII_CHARS[(ptr >>  4) & 0xf];
	*(buffer + 5) = BASE16_ASCII_CHARS[(ptr >>  8) & 0xf];
	*(buffer + 4) = BASE16_ASCII_CHARS[(ptr >> 12) & 0xf];
	*(buffer + 3) = BASE16_ASCII_CHARS[(ptr >> 16) & 0xf];
	*(buffer + 2) = BASE16_ASCII_CHARS[(ptr >> 20) & 0xf];
	*(buffer + 1) = BASE16_ASCII_CHARS[(ptr >> 24) & 0xf];
	*(buffer + 0) = BASE16_ASCII_CHARS[(ptr >> 28) & 0xf];
	__screen_offset__ += 8;

	int i = 0;
	while ((ptr >>= 4))
		i++;
	*(buffer + 6 - i) = '+';
}

/* Writes 16 bytes of ascii into __screen__, non printable characters
 * are replaced by '.'
 */
static inline void	write_16_ascii(const uint8_t *s, size_t size)
{
	uint8_t	*buffer = (__screen__ + __screen_offset__);
	uint8_t *tmp;
	size_t	i;

	i = 0;
	tmp = (uint8_t *)s;
	if (size == 16) {
		 buffer[0] = _Cprint[*(tmp + 0)];
		 buffer[1] = _Cprint[*(tmp + 1)];
		 buffer[2] = _Cprint[*(tmp + 2)];
		 buffer[3] = _Cprint[*(tmp + 3)];
		 buffer[4] = _Cprint[*(tmp + 4)];
		 buffer[5] = _Cprint[*(tmp + 5)];
		 buffer[6] = _Cprint[*(tmp + 6)];
		 buffer[7] = _Cprint[*(tmp + 7)];
		 buffer[8] = _Cprint[*(tmp + 8)];
		 buffer[9] = _Cprint[*(tmp + 9)];
		buffer[10] = _Cprint[*(tmp + 10)];
		buffer[11] = _Cprint[*(tmp + 11)];
		buffer[12] = _Cprint[*(tmp + 12)];
		buffer[13] = _Cprint[*(tmp + 13)];
		buffer[14] = _Cprint[*(tmp + 14)];
		buffer[15] = _Cprint[*(tmp + 15)];
		i += 16;
	} else {
		while (size-- && i < 16)
			buffer[i++] = _Cprint[*tmp++];
	}
	__screen_offset__ += i;
}

/* Writes 16 bytes of data into __screen__, each byte separed by a space
 */
static inline void	write_16_bytes_spaced(const uint8_t *addr, size_t size)
{
	uint8_t		*buffer  = (__screen__ + __screen_offset__);
	uint8_t 	*ptr = (uint8_t *)addr;
	uint8_t 	*tmp = buffer;
	size_t 		pad;

	size = (size < 16 ? 16 : size);
	pad = 16 - size;

	while (size) {
		*(uint32_t*)(buffer) = _xLookup[*ptr++];
		buffer += 3;
		if (--size == 8)
			*(buffer++) = ' ';
	}
	while (pad--) {
		*(uint32_t*)(buffer) = 0x202020;
		buffer += 3;
	}
	__screen_offset__ += buffer - tmp;
}

/* Writes 16 bytes of colored data into __screen__, each byte separed by a space
 */
static inline void	write_16_bytes_spaced_colorized(const uint8_t *addr, size_t n)
{
	uint8_t		*buffer  = (__screen__ + __screen_offset__);
	uint8_t 	*tmp = buffer;
	uint8_t 	*ptr = (uint8_t *)addr;
	size_t 		pad;

	n = (n < 16 ? 16 : n);
	pad = 16 - n;

	while (n) {
		if (isprint(*ptr)) { //printable characters: cyan
			*(uint64_t*)(buffer) = CYN_UINT64;
			buffer += 8;
			while (n && isprint(*ptr)) {
				*(uint32_t*)(buffer) = _xLookup[*ptr++];
				buffer += 3;
				if (--n == 8)
					*(buffer++) = ' ';
			}
		} else {
			if (!*ptr) { // null bytes: grey
				*(uint64_t*)(buffer) = GRY_UINT64;
				buffer += 8;
				while (n && !*ptr) {
					*(uint32_t*)(buffer) = _xLookup[*ptr++];
					buffer += 3;
					if (--n == 8)
						*(buffer++) = ' ';
				}
			} else { // other: white
				*(uint64_t*)(buffer) = END_UINT64;
				buffer += 5;
				while (n && *ptr && !isprint(*ptr)) {
					*(uint32_t*)(buffer) = _xLookup[*ptr++];
					buffer += 3;
					if (--n == 8)
						*(buffer++) = ' ';
				}
			}
		}
	}
	*(uint64_t*)(buffer) = END_UINT64;
	buffer += 5;
	while (pad--) {
		*(uint32_t*)(buffer) = 0x202020;
		buffer += 3;
	}
	__screen_offset__ += buffer - tmp;
}

/* write the bytes as a stream without any formatting. Null bytes are 
 * replaced by ".."
 */
bool raw_bytes_dump(const void *addr, size_t size)
{
	uint8_t	*ptr = (uint8_t *)addr;

	if ((__screen__ = (uint8_t *)malloc((size << 1) + 1)) == 0)
		return (false);
	while (size--)
	{
		*(__screen__ + (__screen_offset__++)) = "0123456789abcdef"[(*ptr >> 4) & 0xf];
		*(__screen__ + (__screen_offset__++)) = "0123456789abcdef"[*ptr & 0xf];
		ptr++;
	}
	*(__screen__ + (__screen_offset__++)) = '\n';
	__dump_screen();
	free(__screen__);
	return (true);
}

/* Mimic of the Linux hexdump -C
*/
bool	classic_hexdump_c(const void *addr, size_t n, size_t start_offset)
{
	size_t		size;
	const void 	*tmp = addr;

	if ((__screen__ = (uint8_t *)malloc(79 << 7)) == NULL)
		return (false);
		
	while (n) {
		size = (16 < n ? 16 : n);
		uint64_t *ptr = (uint64_t *)addr;
		if (tmp != addr
    		&& *(ptr - 2) == *(ptr + 0)
    		&& *(ptr - 1) == *(ptr + 1)
		) {
			if (__screen_offset__) {
				*(uint16_t *)(__screen__ + (__screen_offset__)) = *(uint16_t *)"+\n";
				__screen_offset__ += 2;
				__dump_screen();
			}
		} else {
        	if (__screen_offset__ >= 78 << 7)
				__dump_screen();
			write_offset(addr - tmp + start_offset);
			*(uint32_t *)(__screen__ + __screen_offset__) = *(uint32_t *)":  ";
			__screen_offset__ += 3;
			write_16_bytes_spaced(addr, size);
			*(__screen__ + (__screen_offset__++)) = ' ';
			write_16_ascii(addr, size);
			*(__screen__ + (__screen_offset__++)) = '\n';
		}
        addr += size;
		n -= size;
	}
    if (__screen_offset__)
		__dump_screen();
	free(__screen__);
	return(true);
}
/* mimic of the Linux hexdump -C with colors
*/
bool	classic_hexdump_c_color(const void *addr, size_t n, size_t start_offset)
{
	size_t		size;
	uint64_t 	*ptr;
	const void 	*tmp = addr;

	if ((__screen__ = (uint8_t *)malloc((79 + 16 * 8) << 7)) == NULL)
		return (false);
	while (n) {
		size = (16 < n ? 16 : n);
		ptr = (uint64_t *)addr;
		if (tmp != addr
    		&& *(ptr - 2) == *(ptr + 0)
    		&& *(ptr - 1) == *(ptr + 1)
		) {
			if (__screen_offset__) {
				*(uint16_t *)(__screen__ + (__screen_offset__)) = *(uint16_t *)"*\n";
				__screen_offset__ += 2;
				__dump_screen();
			}
		} else {
        	if (__screen_offset__ >= 78 << 7)
				__dump_screen();
				
			write_offset(addr - tmp + start_offset);
			*(uint32_t *)(__screen__ + __screen_offset__) = *(uint32_t *)":  ";
			__screen_offset__ += 3;
			write_16_bytes_spaced_colorized(addr, size);
			*(__screen__ + (__screen_offset__++)) = ' ';
			write_16_ascii(addr, size);
			*(__screen__ + (__screen_offset__++)) = '\n';
		}
        addr += size;
		n -= size;
	}
    if (__screen_offset__)
		__dump_screen();
	free(__screen__);
	return(true);
}