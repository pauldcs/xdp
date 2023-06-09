#include "xtypes.h"
#include <stdbool.h>


/* Return true if this token is a legal `identifier'; that is, it consists
 * solely of letters, digits, and underscores, and does not begin with a
 * digit.
 */
bool xc_legal_identifier(const char *name)
{
  register const char 	*s;
  unsigned char 		c;

  if (!name
  	|| !(c = *name)
	|| !(XC_ALPHA(c) || (c == '_'))) {
    return (false);
  } 
  for (s = name + 1; (c = *s) != 0; s++)
  {
    if (!(XC_ALNUM(c) || c == '_'))
		  return (false);
  }
  return (true);
}