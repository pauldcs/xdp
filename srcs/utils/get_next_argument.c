#include <stdlib.h>

/* Move one argument forward
*/
char *get_next_argument(int *ac, char ***av)
{
	if (*ac) {
		--(*ac);
		return (*++*av);
	}
	return (NULL);
}