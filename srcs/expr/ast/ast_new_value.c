/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:12:14 by pducos            #+#    #+#             */
/*   Updated: 2023/03/27 23:08:10 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr.h"
#include "expr.h"
#include "xtypes.h"
#include "xleaks.h"
#include <stdlib.h>

t_ast	*ast_new_value(int value)
{
	t_ast	*node;

	node = __xmalloc__(sizeof(t_ast));
	if (!node)
		return (NULL);
	
	node->kind = EXP_VAL;
	node->value = value;
	return (node);
}
