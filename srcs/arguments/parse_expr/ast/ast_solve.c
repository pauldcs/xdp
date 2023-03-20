/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_solve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:07:41 by pducos            #+#    #+#             */
/*   Updated: 2022/11/13 14:57:22 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include <math.h>
#include <stdint.h>

size_t ast_solve(t_ast *ast)
{
	size_t dst, x, y;
	dst = 0;
	if (ast->kind == EXP_VAL)
		dst = ast->value;
	else
	{
		x = ast_solve(ast->binop.left);
		y = ast_solve(ast->binop.right);
		if (ast->kind == EXP_ADD) { dst = x + y; }
		if (ast->kind == EXP_SUB) { dst = x - y; }
		if (ast->kind == EXP_MUL) { dst = x * y; }
		if (ast->kind == EXP_DIV) { dst = x / y; }
		if (ast->kind == EXP_MOD) { dst = x % y; }
	}
	return (dst);
}