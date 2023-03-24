#ifndef __XTYPES_H__
# define __XTYPES_H__

# include <stdint.h>
# include <stdbool.h>

# define cut8 	const uint8_t
# define ut64 	     uint64_t
# define st64 	      int64_t
# define ut32 	     uint32_t
# define st32 	      int32_t
# define ut16 	     uint16_t
# define st16 	      int16_t
# define ut8 	      uint8_t
# define st8 	       int8_t

# define ptr_t         void *
# define diff_t        size_t
# define cstr_t  const char *
# define str_t         char *

# define C_BLACK     "\e[0;30m"
# define C_RED       "\e[0;31m"
# define C_GREENN    "\e[0;32m"
# define C_YELLOW    "\e[0;33m"
# define C_BLUE      "\e[0;34m"
# define C_MAGENTA   "\e[0;35m"
# define C_CYAN      "\e[0;36m"
# define C_LIGHTGREY "\x1b[37;1m"
# define C_WHITE     "\x1b[2;37m"
# define C_GREY      "\x1b[90m"
# define C_RESET     "\e[0m"

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

#define XC_ALNUM(c)	(_CharType[(int)(c)] & (_DI|_LO|_UP|_XA))
#define XC_ALPHA(c)	(_CharType[(int)(c)] & (_LO|_UP|_XA))
#define XC_CNTRL(c)	(_CharType[(int)(c)] & (_BB|_CN))
#define XC_DIGIT(c)	(_CharType[(int)(c)] & _DI)
#define XC_GRAPH(c)	(_CharType[(int)(c)] & (_DI|_LO|_PU|_UP|_XA))
#define XC_LOWER(c)	(_CharType[(int)(c)] & _LO)
#define XC_PRINT(c)	(_CharType[(int)(c)] & (_DI|_LO|_PU|_SP|_UP|_XA))
#define XC_PUNCT(c)	(_CharType[(int)(c)] & _PU)
#define XC_SPACE(c)	(_CharType[(int)(c)] & (_CN|_SP|_XS))
#define XC_UPPER(c)	(_CharType[(int)(c)] & _UP)
#define XC_XDIGIT(c)	(_CharType[(int)(c)] & _XD)

extern const uint8_t  _PrintByte[256];
extern const uint16_t _B16Pair[256];
extern const uint32_t _CharColor[256];
extern const uint32_t _B16PairSpaced[256];
extern const uint16_t _CharType[256];

bool xc_legal_identifier(const char *name);
bool xc_legal_number (const char *str, intmax_t *result);

#endif /* __XTYPES_H__ */