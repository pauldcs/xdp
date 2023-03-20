#include <stdint.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

const char	*str_to_uint64(const char *str, size_t *result)
{
	long tmp;

	tmp = 0;
    if (*str == '0' && *(str + 1) == 'x') {
        char *endptr;
        tmp = strtol(str, &endptr, 16);
        str = endptr;
        if (errno == ERANGE
            || tmp > INT_MAX
            || *str)
        return NULL;
    } else {
        while (*str >= '0' && *str <= '9')
        {
            tmp *= 10;
            tmp += *(str++) & 0xCF;
            if (tmp > INT_MAX)
                return (NULL);
        }
    }
	*result = tmp;
	if (*str)
		return (NULL);
	return (str);
}