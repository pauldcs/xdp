#ifndef __STRDUMP_H__
# define __STRDUMP_H__

bool str_dump(const uint8_t* addr, size_t n, size_t len);

size_t strd_compare(const char *s1, const char *s2);

/* Compares a string with a pattern and returns true
 * if the string matches the pattern, or false if it does not. The pattern
 * can contain the special characters `*` and `?`
 */
bool strp_compare(char *str, char *pattern);

#endif