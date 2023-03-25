#ifndef __HEX_H__
# define __HEX_H__

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

	/*-- Convert --*/
size_t	xd_ascii_16_bytes(uint8_t *dst, const uint8_t *src, size_t n);
size_t	xd_data_16_bytes(uint8_t *dst, const uint8_t *src, size_t n);
size_t	xd_data_16_bytes_color(const uint8_t *addr, size_t n, uint8_t *buffer);
size_t	xd_pointer_8_bytes(uint8_t *dst, const uintptr_t p);
size_t	xd_pointer_p8_bytes(uint8_t *dst, const uintptr_t p);

	/*-- Hexdump --*/
# define N_LINES 512
# define LINE_LEN (77 + 1)
# define SCREEN_BUFFER_SIZE ((LINE_LEN) * N_LINES)
# define BASE16_ASCII_CHARS "0123456789abcdef"

ssize_t	xd_dump_lines(const uint8_t *addr, size_t n, size_t offset);
ssize_t	xd_dump_lines_color(const uint8_t *addr, size_t n, size_t offset);

	/*-- Lookup --*/
# define _RED    0x00000001
# define GREEN   0x00000010
# define YELLOW  0x00000100
# define BLUE    0x00001000
# define MAGENTA 0x00010000
# define CYAN    0x00100000
# define WHITE   0x01000000
# define GREY    0x10000000

#endif /* __HEX_H__ */