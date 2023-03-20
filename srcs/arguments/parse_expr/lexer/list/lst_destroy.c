/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:29:25 by pducos            #+#    #+#             */
/*   Updated: 2022/11/09 01:20:31 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

void	lst_destroy(t_token **toklist)
{
	t_token	*node;
	t_token	*tmp;

	tmp = *toklist;
	node = tmp;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}	
	*toklist = NULL;
}