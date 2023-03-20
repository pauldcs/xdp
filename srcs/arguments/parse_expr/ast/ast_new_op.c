/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:12:14 by pducos            #+#    #+#             */
/*   Updated: 2022/11/13 00:44:29 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

t_ast	*ast_new_op(t_token_kind kind)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	else if (kind == TOKEN_ADD)		node->kind = EXP_ADD;
	else if (kind == TOKEN_SUB)		node->kind = EXP_SUB;
	else if (kind == TOKEN_MUL)		node->kind = EXP_MUL;
	else if (kind == TOKEN_DIV)		node->kind = EXP_DIV;
	else if (kind == TOKEN_MOD)		node->kind = EXP_MOD;
	else if (kind == TOKEN_LPAREN)	node->kind = EXP_LPAREN;
	else if (kind == TOKEN_RPAREN)  node->kind = EXP_RPAREN;
	node->binop.left = NULL;
	node->binop.right = NULL;
	return (node);
}
