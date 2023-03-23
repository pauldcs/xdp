#ifndef __LIBXDUMP__
# define __LIBXDUMP__

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

#define BLK_UINT64 	*(uint64_t*)"\e[0;30m"
#define RED_UINT64 	*(uint64_t*)"\e[0;31m"
#define GRN_UINT64 	*(uint64_t*)"\e[0;32m"
#define YEL_UINT64 	*(uint64_t*)"\e[0;33m"
#define BLU_UINT64 	*(uint64_t*)"\e[0;34m"
#define MAG_UINT64 	*(uint64_t*)"\e[0;35m"
#define CYN_UINT64 	*(uint64_t*)"\e[0;36m"
#define WHT_UINT64 	*(uint64_t*)"\e[0;37m"
#define GRY_UINT64 	*(uint64_t*)"\x1b[2;37m"
#define END_UINT64 	*(uint64_t*)"\e[0m"

# define BASE16_ASCII_CHARS "0123456789abcdef"

	/*-- Convert --*/
size_t	xd_ascii_16_bytes(uint8_t *dst, const uint8_t *src, size_t n);
size_t	xd_data_16_bytes(uint8_t *dst, const uint8_t *src, size_t n);
size_t	xd_data_16_bytes_color(const uint8_t *addr, size_t n, uint8_t *buffer);
size_t	xd_pointer_8_bytes(uint8_t *dst, const uintptr_t p);
size_t	xd_pointer_p8_bytes(uint8_t *dst, const uintptr_t p);

	/*-- Hexdump --*/
# define N_LINES 512
# define LINE_LEN (78 + 1)
# define SCREEN_BUFFER_SIZE ((LINE_LEN) * N_LINES)

ssize_t	xd_dump_lines(const uint8_t *addr, size_t n, size_t offset);
ssize_t	xd_dump_lines_color(const uint8_t *addr, size_t n, size_t offset);

	/*-- Lookup --*/

# define _RED 0x00000001
# define GREEN 0x00000010
# define YELLOW 0x00000100
# define BLUE 0x00001000
# define MAGENTA 0x00010000
# define CYAN 0x00100000
# define WHITE 0x01000000
# define GREY 0x10000000

extern const uint8_t  _PrintByte[256];
extern const uint16_t _B16Pair[256];
extern const uint16_t _CharType[256];
extern const uint32_t _CharColor[256];
extern const uint32_t _B16PairSpaced[256];

	/*-- Ctypes --*/
#define _XA		0x200 /* extra alphabetic */
#define _XS		0x100 /* extra space */
#define _BB		0x80 /* BEL, BS, etc. */
#define _CN		0x40 /* CR, FF, HT, NL, VT */
#define _DI		0x20 /* '0'-'9' */
#define _LO		0x10 /* 'a'-'z' */
#define _PU		0x08 /* punctuation */
#define _SP		0x04 /* space */
#define _UP		0x02 /* 'A'-'Z' */
#define _XD		0x01 /* '0'-'9', 'A'-'F', 'a'-'f' */

#define XDI (_DI|_XD)
#define XLO (_LO|_XD)
#define XUP (_UP|_XD)

#define xd_isalnum(c)	(_CharType[(int)(c)] & (_DI|_LO|_UP|_XA))
#define xd_isalpha(c)	(_CharType[(int)(c)] & (_LO|_UP|_XA))
#define xd_iscntrl(c)	(_CharType[(int)(c)] & (_BB|_CN))
#define xd_isdigit(c)	(_CharType[(int)(c)] & _DI)
#define xd_isgraph(c)	(_CharType[(int)(c)] & (_DI|_LO|_PU|_UP|_XA))
#define xd_islower(c)	(_CharType[(int)(c)] & _LO)
#define xd_isprint(c)	(_CharType[(int)(c)] & (_DI|_LO|_PU|_SP|_UP|_XA))
#define xd_ispunct(c)	(_CharType[(int)(c)] & _PU)
#define xd_isspace(c)	(_CharType[(int)(c)] & (_CN|_SP|_XS))
#define xd_isupper(c)	(_CharType[(int)(c)] & _UP)
#define xd_isxdigit(c)	(_CharType[(int)(c)] & _XD)

#endif /* __LIBXDUMP__ */