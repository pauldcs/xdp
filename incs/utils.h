#ifndef __UTILS_H__
# define __UTILS_H__

# include <stddef.h>
# include <sys/types.h>

void 		__usage(void);
char 		*get_next_argument(int *ac, char ***av);
const char	*str_to_uint64(const char *str, size_t *result);
size_t		write_all(int fd, const void *buf, size_t s);
ssize_t 	read_from_fd(int fd, char **data);

/*
    Compares a string with a pattern and returns true
    if the string matches the pattern, or false if it does not. The pattern
    can contain the special characters * and ?, which have the following
*/
bool strpcmp(char *str, char *pattern);

size_t strdcmp(const char *s1, const char *s2, size_t max);

#endif /* __UTILS_H__ */