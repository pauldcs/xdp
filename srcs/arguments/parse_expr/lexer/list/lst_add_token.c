/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:29:25 by pducos            #+#    #+#             */
/*   Updated: 2023/03/20 15:38:19 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr_lexer.h"
#include <stdint.h>

void	lst_add_token(t_token **token_list, t_token *token, t_token_kind kind)
{
	t_token	*node;

	token->kind = kind;
	if (!*token_list)
		*token_list = token;
	else
	{
		node = *token_list;
		while (node->next)
			node = node->next;
		node->next = token;
	}
}
