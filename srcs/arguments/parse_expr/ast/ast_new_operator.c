/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:12:14 by pducos            #+#    #+#             */
/*   Updated: 2023/03/20 15:38:46 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr_parser.h"
#include <string.h>
#include <stdlib.h>

t_ast	*ast_new_operator(t_token_kind kind)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	memset(node, 0, sizeof(t_ast));

	if      (kind == TOKEN_ADD)		node->kind = EXP_ADD;
	else if (kind == TOKEN_SUB)		node->kind = EXP_SUB;
	else if (kind == TOKEN_MUL)		node->kind = EXP_MUL;
	else if (kind == TOKEN_LPAREN)	node->kind = EXP_LPAREN;
	else if (kind == TOKEN_RPAREN)  node->kind = EXP_RPAREN;

	return (node);
}
