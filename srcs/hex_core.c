#include "hexdump.h"
#include "xlookup.h"
#include "c_types.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

static uint8_t *__screen__;
static size_t   __screen_offset__ = 0;

static size_t	write_all(int fd, const void *buf, size_t s)
{
	/* Forces to write the buffer fully if write() failes, 
     * it's ok if this ends up looping endlessly.
     */
	ssize_t	c;
	size_t	ret;

	ret = 0;
	while (s)
	{
		c = write(fd, buf + ret, s);
		if (c == -1)
			continue ;
		ret += c;
		s -= c;
	}
	return (ret);
}

static void __dump_screen(void)
{
	/* Dumps the content of __screen__ to stdout
	 */
	write_all(STDOUT_FILENO,
		__screen__,
		__screen_offset__);
	__screen_offset__ = 0;
}

static inline void	write_pointer(const uintptr_t p, size_t width)
{
	/* Writes a pointer in hex format into __screen__
 	 */
	uint8_t		*buffer = (uint8_t *)(__screen__ + __screen_offset__);
	uintptr_t	ptr;
	int			i;

	i = width;
	ptr = (uintptr_t)p;
	do {
		buffer[--i] = "0123456789abcdef"[ptr & 0xf];
		ptr >>= 4;
	} while (ptr && i);
	while (i)
		buffer[--i] = '0';
	__screen_offset__ += width;
}

static inline void	write_16_bytes_spaced(const uint8_t *addr, size_t size)
{
	/* Writes 16 bytes of data into __screen__, each byte separed by a space
 	 */
	uint8_t		*buffer  = (__screen__ + __screen_offset__);
	uint8_t 	*ptr = (uint8_t *)addr;
	uint8_t 	*tmp = buffer;
	size_t 		pad;

	size = (size < 16 ? 16 : size);
	pad = 16 - size;

	while (size) {
		*(uint32_t*)(buffer) = _xlookup[*ptr++];
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

static inline void	write_16_bytes_spaced_colorized(const uint8_t *addr, size_t n)
{
	/* Writes 16 bytes of colored data into __screen__, each byte separed by a space
 	 */
	uint8_t		*buffer  = (__screen__ + __screen_offset__);
	uint8_t 	*tmp = buffer;
	uint8_t 	*ptr = (uint8_t *)addr;
	size_t 		pad;

	n = (n < 16 ? 16 : n);
	pad = 16 - n;

	while (n) {
		if (isprint(*ptr)) {
			*(uint64_t*)(buffer) = CYN_UINT64;
			buffer += 8;
			while (n && isprint(*ptr)) {
				*(uint32_t*)(buffer) = _xlookup[*ptr++];
				buffer += 3;
				if (--n == 8)
					*(buffer++) = ' ';
			}
		} else {
			*(uint64_t*)(buffer) = GRY_UINT64;
			buffer += 8;
			while (n && !isprint(*ptr)) {
				*(uint32_t*)(buffer) = _xlookup[*ptr++];
				buffer += 3;
				if (--n == 8)
					*(buffer++) = ' ';
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

static inline void	write_16_ascii(const uint8_t *s, size_t size)
{
	/* Writes 16 bytes of ascii into __screen__, non printable characters
 	 * are replaced by '.'
 	 */
	uint8_t	*buffer = (__screen__ + __screen_offset__);
	uint8_t *tmp;
	size_t	i;

	i = 0;
	tmp = (uint8_t *)s;
	while (size-- && i < 16)
		buffer[i++] = ctyp_print[*tmp++];
	__screen_offset__ += i;
}

bool raw_bytes_dump(const void *addr, size_t size)
{
	/* write the bytes as a stream without any formatting. Null bytes are 
 	 * replaced by ".."
	 */
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

bool	classic_hexdump_c(const void *addr, size_t n)
{
	/* mimic of the Linux hexdump -C
 	*/
	size_t		size;
	uint64_t 	*ptr;
	const void 	*tmp = addr;

	if ((__screen__ = (uint8_t *)malloc(79 << 7)) == NULL)
		return (false);
	while (n) {
		size = (16 < n ? 16 : n);
		ptr = (uint64_t *)addr;
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
			write_pointer(addr - tmp, 10);
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

bool	classic_hexdump_c_color(const void *addr, size_t n)
{
	/* mimic of the Linux hexdump -C
 	*/
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
				*(uint16_t *)(__screen__ + (__screen_offset__)) = *(uint16_t *)"+\n";
				__screen_offset__ += 2;
				__dump_screen();
			}
		} else {
        	if (__screen_offset__ >= 78 << 7)
				__dump_screen();
				
			write_pointer(addr - tmp, 10);
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