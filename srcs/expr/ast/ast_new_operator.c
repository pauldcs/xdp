/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:12:14 by pducos            #+#    #+#             */
/*   Updated: 2023/03/21 00:18:23 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr/expr_parser.h"
#include <string.h>
#include <stdlib.h>

t_ast	*ast_new_operator(t_token_kind kind)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	memset(node, 0, sizeof(t_ast));

	switch (kind)
	{
		case TOKEN_ADD:
			node->kind = EXP_ADD; break ;
		case TOKEN_SUB:
			node->kind = EXP_SUB; break ;
		case TOKEN_MUL:
			node->kind = EXP_MUL; break ;
		case TOKEN_LPAREN:
			node->kind = EXP_LPAREN; break ;
		case TOKEN_RPAREN:
			node->kind = EXP_RPAREN; break ;
		default:
			break ;
	}
	return (node);
}
