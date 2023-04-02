#include "xleaks.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool	is_separator(int c, char *sep)
{
	while (*sep)
	{
		if (c == *sep)
			return (true);
		sep++;
	}
	return (false);
}

static size_t	count_elements(char const *str, char *sep)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str && is_separator(*str, sep))
			str++;
		if (*str)
			count++;
		while (*str && !is_separator(*str, sep))
			str++;
	}
	return (count);
}

char	**ft_split(char const *str, char *sep)
{
	size_t	size = count_elements(str, sep);
	char	**split;
	size_t	i;

	split = malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (NULL);
	while (*str && is_sep(*str, sep))
		str++;
	while (*str)
	{
		i = 0;
		while (str[i] && (!is_separator(str[i], sep)))
			i++;
		if (i)
		{
			*(split++) = strndup(str, i);
			str += i;
		}
		else
			str++;
	}
	*split = NULL;
	return (split - size);
}