#ifndef __UTILS_H__
# define __UTILS_H__

#include <stddef.h>

int         clamp(int n, int min, int max);
char        **ft_split(char const *str, char *sep);
const char  *str_to_uint64(const char *str, size_t *result);
size_t      string_distance_cmp(const char *s1, const char *s2);
size_t      xwrite(int fd, const unsigned char *buf, size_t nbytes);

#endif /* __UTILS_H__ */