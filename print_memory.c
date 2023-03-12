#include <ctype.h>
#include <unistd.h>

static void	print_addr(const uintptr_t p)
{
	uint64_t	ptr;
	char		buffer[16];
	int			i;

	i = 16;
	if (p)
	{
		ptr = (uint64_t)p;
		while (ptr && i)
		{
			buffer[--i] = "0123456789abcdef"[ptr & 0xf];
			ptr >>= 4;
		}
	}
	else
		buffer[--i] = '0';
	while (i)
		buffer[--i] = '0';
	write(STDOUT_FILENO, "0x", 2);
	write(STDOUT_FILENO, buffer, 16);
}

static void	print_data(const void *addr, size_t size)
{
	unsigned char	*ptr;
	unsigned char	buffer[49];
	size_t			i;

	i = 0;
	ptr = (unsigned char *)addr;
	while (size-- && i < 49)
	{
		if (*ptr)
		{
			if (*ptr & 0xf0)
				buffer[i++] = "0123456789abcdef"[(*ptr >> 4) & 0xf];
			else
				buffer[i++] = ' ';
			buffer[i++] = "0123456789abcdef"[*ptr & 0xf];
		}
		else
		{
			buffer[i++] = ' ';
			buffer[i++] = ' ';
		}
		buffer[i++] = ' ';
		ptr++;
	}
	while (i < 49)
		buffer[i++] = ' ';
	write(STDOUT_FILENO, buffer, i - 2);
}

static void	print_ascii(const void *s, size_t size)
{
	char			*tmp;
	unsigned char	buffer[16];
	size_t			i;

	i = 0;
	tmp = (char *)s;
	while (size-- && i < 16)
	{
		if (isprint(*tmp))
			buffer[i++] = *tmp;
		else
			buffer[i++] = '.';
		tmp++;
	}
	write(STDOUT_FILENO, buffer, i);
}

void	print_memory(const void *addr, size_t n)
{
	size_t	size;

	while (n)
	{
		size = n;
		if (size > 16)
			size = 16;
		print_addr((uintptr_t)addr);
		write(STDOUT_FILENO, ":  ", 3);
		print_data(addr, size);
		write(STDOUT_FILENO,  "  ", 2);
		print_ascii(addr, size);
		write(STDOUT_FILENO,  "\n", 1);
		addr += size;
		n -= size;
	}
	write(STDOUT_FILENO, "\n", 1);
}

int main(void)
{
	print_memory("hellok", 128);
/*
	0x0000000104d1ff9d:  68 65 6c 6c 6f 6b    30 31 32 33 34 35 36 37 38  hellok.012345678
	0x0000000104d1ffad:  39 61 62 63 64 65 66    30 78     1          1c  9abcdef.0x......
	0x0000000104d1ffbd:                       1c                      1c  ................
	0x0000000104d1ffcd:            2          dc 39       34          34  ........9..4...4
	0x0000000104d1ffdd:           71 3f                   34           3  ...q?......4....
	0x0000000104d1ffed:            c     1    10     1                    ................
	0x0000000104d1fffd:         4 d4 7c 84 8f  1          68 13 eb ea  1  ....|......h....
	0x0000000104d2000d:           84 9d 81 8f  1          6c 1b 8e 8f  1  ...........l....
*/
	return (0);
}