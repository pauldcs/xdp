/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:12:14 by pducos            #+#    #+#             */
/*   Updated: 2023/03/20 15:22:54 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr_parser.h"
#include "expr_lexer.h"
#include <stdlib.h>

t_ast	*ast_new_value(int value)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->kind = EXP_VAL;
	node->value = value;
	return (node);
}
