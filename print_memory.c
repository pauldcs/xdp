/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:38:08 by pducos            #+#    #+#             */
/*   Updated: 2022/09/28 03:40:27 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (0);
}