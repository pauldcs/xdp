#ifndef __HEX_H__
# define __HEX_H__

# include "xtypes.h"
# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

	/*-- Convert --*/
size_t	xd_ascii_16_bytes(ut8 *dst, const ut8 *src, size_t n);
size_t	xd_data_16_bytes(cut8 *dst, cut8 *src, size_t n);
size_t	xd_data_16_bytes_color(const ut8 *addr, size_t n, ut8 *buffer);
size_t	xd_pointer_8_bytes(ut8 *dst, const uintptr_t p);
size_t	xd_pointer_p8_bytes(ut8 *dst, const uintptr_t p);

	/*-- Hexdump --*/
# define N_LINES 512
# define LINE_LEN (77 + 1)
# define SCREEN_BUFFER_SIZE ((LINE_LEN) * N_LINES)
# define BASE16_ASCII_CHARS "0123456789abcdef"

bool	xd_dump_fd(int fd, size_t n, size_t offset);
ssize_t	xd_dump_lines(const ut8 *addr, size_t n, size_t offset);
ssize_t	xd_dump_lines_color(const ut8 *addr, size_t n, size_t offset);

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