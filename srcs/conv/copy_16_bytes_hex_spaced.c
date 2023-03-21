#include <stdint.h>
#include <stddef.h>

void	write_16_bytes_spaced(const uint8_t *addr, size_t size, uint8_t *buffer)
{
	uint8_t 	*ptr = (uint8_t *)addr;
	uint8_t 	*tmp = buffer;
	size_t 		pad;

	size = (size > 16 ? 16 : size);
	pad = 16 - size;

	while (size) {
		*(uint32_t*)(buffer) = _xLookup[*ptr++];
		buffer += 3;
		--size;
	}
	while (pad--) {
		*(uint32_t*)(buffer) = 0x202020;
		buffer += 3;
	}
	__screen_offset__ += buffer - tmp;
}