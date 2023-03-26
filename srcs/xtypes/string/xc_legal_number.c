#include "xtypes.h"
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

/* Return non-zero if the characters pointed to by `str` constitute a
 * valid number.
 */
bool xc_legal_number (const char *str, intmax_t *result)
{
	intmax_t 	value;
	char 		*ep;

	if (result)
		*result = 0;

	if (!str)
		return (false);

	value = strtoimax(str, &ep, 10);
	if (errno || ep == str)
		return (false);

	while (XC_SPACE(*ep))
		ep++;

	if (*str && !*ep)
    {
		if (result)
			*result = value;
		return (true);
    }
  return (false);
}