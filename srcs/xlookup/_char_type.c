#include "xlookup.h"
#include <stdint.h>

const uint16_t _char_type[256] = {
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