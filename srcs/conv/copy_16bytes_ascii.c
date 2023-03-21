#include <stdint.h>
#include <stddef.h>

/* Writes 16 bytes of ascii into __screen__, non printable characters
 * are replaced by '.'
 */
size_t	copy_16bytes_ascii(const uint8_t *s, size_t size, uint8_t *buffer)
{
	size_t	ret = 0;

	if (size == 16) {
		buffer[0] = _Cprint[*(s + 0)];
		buffer[1] = _Cprint[*(s + 1)];
		buffer[2] = _Cprint[*(s + 2)];
		buffer[3] = _Cprint[*(s + 3)];
		buffer[4] = _Cprint[*(s + 4)];
		buffer[5] = _Cprint[*(s + 5)];
		buffer[6] = _Cprint[*(s + 6)];
		buffer[7] = _Cprint[*(s + 7)];
		buffer[8] = _Cprint[*(s + 8)];
		buffer[9] = _Cprint[*(s + 9)];
		buffer[10] = _Cprint[*(s + 10)];
		buffer[11] = _Cprint[*(s + 11)];
		buffer[12] = _Cprint[*(s + 12)];
		buffer[13] = _Cprint[*(s + 13)];
		buffer[14] = _Cprint[*(s + 14)];
		buffer[15] = _Cprint[*(s + 15)];
		ret += 16;
	} else {
		uint8_t *tmp = (uint8_t *)s;
		while (size-- && ret < 16)
			buffer[ret++] = _Cprint[*tmp++];
	}
	return (ret);
}