/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:29:25 by pducos            #+#    #+#             */
/*   Updated: 2023/03/20 15:15:00 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr_lexer.h"
#include <stdlib.h>

void	lst_destroy(t_token **token_list)
{
	t_token	*node;
	t_token	*tmp;

	tmp = *token_list;
	node = tmp;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}	
	*token_list = NULL;
}