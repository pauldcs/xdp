/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addtok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:29:25 by pducos            #+#    #+#             */
/*   Updated: 2022/11/13 14:35:23 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdint.h>

void	lst_addtok(t_token **toklist, t_token *tok, t_token_kind kind)
{
	t_token	*node;

	tok->kind = kind;
	if (!*toklist)
		*toklist = tok;
	else
	{
		node = *toklist;
		while (node->next)
			node = node->next;
		node->next = tok;
	}
}
