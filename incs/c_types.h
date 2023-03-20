#ifndef __C_TYPES_H__
# define __C_TYPES_H__

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

#define isalnum(c)	(_Ctype[(int)(c)] & (_DI|_LO|_UP|_XA))
#define isalpha(c)	(_Ctype[(int)(c)] & (_LO|_UP|_XA))
#define iscntrl(c)	(_Ctype[(int)(c)] & (_BB|_CN))
#define isdigit(c)	(_Ctype[(int)(c)] & _DI)
#define isgraph(c)	(_Ctype[(int)(c)] & (_DI|_LO|_PU|_UP|_XA))
#define islower(c)	(_Ctype[(int)(c)] & _LO)
#define isprint(c)	(_Ctype[(int)(c)] & (_DI|_LO|_PU|_SP|_UP|_XA))
#define ispunct(c)	(_Ctype[(int)(c)] & _PU)
#define isspace(c)	(_Ctype[(int)(c)] & (_CN|_SP|_XS))
#define isupper(c)	(_Ctype[(int)(c)] & _UP)
#define isxdigit(c)	(_Ctype[(int)(c)] & _XD)
#define tolower(c)	_Tolower[(int)(c)]
#define toupper(c)	_Toupper[(int)(c)]

		/* static data */
static const short ctyp_tab[256] = { /* EOF */
   0, _BB, _BB, _BB, _BB, _BB, _BB, _BB,
 _BB, _CN, _CN, _CN, _CN, _CN, _BB, _BB,
 _BB, _BB, _BB, _BB, _BB, _BB, _BB, _BB,
 _BB, _BB, _BB, _BB, _BB, _BB, _BB, _BB,
 _SP, _PU, _PU, _PU, _PU, _PU, _PU, _PU,
 _PU, _PU, _PU, _PU, _PU, _PU, _PU, _PU,
 XDI, XDI, XDI, XDI, XDI, XDI, XDI, XDI,
 XDI, XDI, _PU, _PU, _PU, _PU, _PU, _PU,
 _PU, XUP, XUP, XUP, XUP, XUP, XUP, _UP,
 _UP, _UP, _UP, _UP, _UP, _UP, _UP, _UP,
 _UP, _UP, _UP, _UP, _UP, _UP, _UP, _UP,
 _UP, _UP, _UP, _PU, _PU, _PU, _PU, _PU,
 _PU, XLO, XLO, XLO, XLO, XLO, XLO, _LO,
 _LO, _LO, _LO, _LO, _LO, _LO, _LO, _LO,
 _LO, _LO, _LO, _LO, _LO, _LO, _LO, _LO,
 _LO, _LO, _LO, _PU, _PU, _PU, _PU, _BB,
 };

const short *_Ctype = &ctyp_tab[0];

static const char _Cprint[256] = {
    '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
    '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
    ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
    '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '.',
    '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
    '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
    '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
    '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
    '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
    '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
    '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
    '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
};

#endif /* __C_CprintTYPES_H__ */