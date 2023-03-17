#include "reader.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

static bool	is_sep(char *sep, int c)
{
	while (*sep)
	{
		if (*sep == c)
			return (true);
		sep++;
	}
	return (false);
}

static bool	init_buf(t_reader *r, uint8_t **buf, size_t *size)
{
	if (r->save.buf)
	{
		*buf = r->save.buf;
		*size = r->save.size;
		r->cap = *size;
	}
	else
	{
		r->cap = BUFF_SIZE;
		*size = 0;
		if (!r_alloc(buf, BUFF_SIZE))
			return (false);
	}
	r->save.buf = NULL;
	r->save.size = 0;
	r->checked = 0;
	return (true);
}

static bool	search_char(t_reader *r, char *sep, uint8_t *buf, size_t len)
{
	uint8_t	*ptr;
	size_t	n;

	ptr = buf + r->checked;
	n = len - r->checked;
	while (n--)
	{
		r->checked++;
		if (!is_sep(sep, *ptr) && ptr++)
			continue ;
		*ptr++ = 0;
		len -= ptr - buf;
		if (len)
		{
			if (!r_alloc(&r->save.buf, len)
				|| !r_memcpy(r->save.buf, ptr, len))
				return (false);
			r->save.size = len;
		}
		return (true);
	}
	return (false);
}

ssize_t	reader(uint8_t **buf, t_reader *r, char *sep)
{
	size_t	size;
	int		ret;

	if (!init_buf(r, buf, &size))
		return (R_ERROR);
	while (!search_char(r, sep, *buf, size))
	{
		if (size >= r->cap
			&& !r_realloc(buf, &r->cap, size, 2 * r->cap))
			return (R_ERROR);
		ret = read(r->fd, *buf + size, r->cap - size);
		if (ret == -1
			|| (!ret && !size))
			return (free(*buf), R_ERROR);
		else if (!ret)
			return (size);
		size += ret;
	}
	return (size - r->save.size - 1);
}