#ifndef __CONVERT_H__
# define __CONVERT_H__

size_t	copy_pointer_64(const uintptr_t p, uint8_t *buffer);
size_t	copy_pointer_64_plus(const uintptr_t p, uint8_t *buffer);
size_t	copy_16bytes_ascii(const uint8_t *s, size_t size, uint8_t *buffer);


#endif /* __CONVERT_H__ */