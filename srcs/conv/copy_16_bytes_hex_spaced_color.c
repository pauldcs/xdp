#include <stdint.h>
#include <stddef.h>

/* Writes 16 bytes of colored data into __screen__, each byte separed by a space
 */
void	write_16_bytes_spaced_colorized(const uint8_t *addr, size_t n, uint8_t *buffer)
{
	uint8_t 	*tmp = buffer;
	uint8_t 	*ptr = (uint8_t *)addr;
	size_t 		pad;

	n = (n > 16 ? 16 : n);
	pad = 16 - n;

	while (n) {
		if (isprint(*ptr)) { //printable characters: cyan
			*(uint64_t*)(buffer) = CYN_UINT64;
			buffer += 8;
			while (n && isprint(*ptr)) {
				*(uint32_t*)(buffer) = _xLookup[*ptr++];
				buffer += 3;
				--n;
			}
		} else {
			if (!*ptr) { // null bytes: grey
				*(uint64_t*)(buffer) = GRY_UINT64;
				buffer += 8;
				while (n && !*ptr) {
					*(uint32_t*)(buffer) = _xLookup[*ptr++];
					buffer += 3;
					--n;
				}
			} else { // other: white
				*(uint64_t*)(buffer) = END_UINT64;
				buffer += 5;
				while (n && *ptr && !isprint(*ptr)) {
					*(uint32_t*)(buffer) = _xLookup[*ptr++];
					buffer += 3;
					--n;
				}
			}
		}
	}
	*(uint64_t*)(buffer) = END_UINT64;
	buffer += 5;
	while (pad--) {
		*(uint32_t*)(buffer) = 0x202020;
		buffer += 3;
	}
	__screen_offset__ += buffer - tmp;
}