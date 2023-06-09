/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_solve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:07:41 by pducos            #+#    #+#             */
/*   Updated: 2023/03/26 20:08:28 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr.h"
#include "expr.h"

size_t ast_solve(t_ast *ast)
{
	size_t result = 0;
	
	if (ast->kind == EXP_VAL) {
		result = ast->value;
	
	} else {
		size_t x = ast_solve(ast->binop.left);
		size_t y = ast_solve(ast->binop.right);

		switch (ast->kind)
		{
			case EXP_ADD:
				result = x + y; break;
			case EXP_SUB:
				result = x - y; break;
			case EXP_MUL:
				result = x * y; break;
			default: 
				break;
		}
	}
	return (result);
}