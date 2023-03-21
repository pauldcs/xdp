/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:16:30 by pducos            #+#    #+#             */
/*   Updated: 2022/10/02 23:51:34 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include <fcntl.h>
#include <stdbool.h>

t_reader	*reader_init(const char *file)
{
	static t_reader	r;

	r.fd = open(file, O_RDONLY);
	if (r.fd != -1)
	{
		r.save.buf = NULL;
		r.save.size = 0;
		return (&r);
	}
	return (NULL);
}
