#include <stdbool.h>

bool xstrp_compare(char *str, char *pattern)
{
    if (*pattern == '\0')
        return *str == '\0';

    while (*str != '\0' && *pattern != '\0')
	{
        if (*pattern == '*')
		{
            do 
			{
                if (xstrp_compare(str, pattern + 1))
                return (true);
            } while (*str++ != '\0');
            return (false);
        }

        if (*pattern == '?')
		{
            if (*str == '\0')
                return (false);
            pattern++;
            str++;
            continue;
        }

        if (*str != *pattern)
            return (false);
        pattern++;
        str++;
    }

    if (*str == '\0')
	{
        while (*pattern == '*')
            pattern++;
        return *pattern == '\0';
    }
    return (false);
}