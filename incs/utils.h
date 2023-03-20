#ifndef __UTILS_H__
# define __UTILS_H__

void 		__usage(void);
const char	*str_to_uint64(const char *str, size_t *result);
size_t		write_all(int fd, const void *buf, size_t s);

#endif /* __UTILS_H__ */