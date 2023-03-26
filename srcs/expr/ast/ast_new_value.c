/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:12:14 by pducos            #+#    #+#             */
/*   Updated: 2023/03/26 16:57:05 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr/expr_parser.h"
#include "expr/expr_lexer.h"
#include "xtypes.h"
#include "xmem.h"

t_ast	*ast_new_value(int value)
{
	t_ast	*node;

	if (!xmem_alloc((ptr_t *)&node,sizeof(t_ast)))
		return (NULL);
	
	node->kind = EXP_VAL;
	node->value = value;
	return (node);
}
