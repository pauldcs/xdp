/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:16:42 by pducos            #+#    #+#             */
/*   Updated: 2022/10/02 23:52:30 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include <unistd.h>
#include <stdlib.h>

void	reader_destroy(t_reader *reader)
{
	if (reader->save.buf)
	{
		free((void *)reader->save.buf);
		reader->save.buf = NULL;
		reader->save.size = 0;
	}
	close(reader->fd);
	reader->fd = -1;
}
