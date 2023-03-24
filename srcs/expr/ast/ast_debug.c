/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:32:39 by pducos            #+#    #+#             */
/*   Updated: 2023/03/24 15:28:41 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug/logging.h"
#include "expr/expr_parser.h"
#include <stdio.h>
#include <stdio.h>

static void	inner(t_ast *ast, size_t depth);

static const char	*g_ast_names[] = {
	"lparen", "rparen", "val",
	"operator='*'", "operator='+'", "operator='-'"
};

static void	put_binop(t_ast *ast, size_t depth)
{
	fprintf(stdout, "\n");
	inner(ast->binop.left, depth + 1);
	inner(ast->binop.right, depth + 1);
}

static void	inner(t_ast *ast, size_t depth)
{
	size_t	i;

	i = 0;
	fprintf(stdout, "t_ast:");
	while (i++ < depth)
		fprintf(stdout, "%4s", "");
	if (ast->kind == EXP_VAL)
		fprintf(stdout, " - value='%d'\n", ast->value);
	else
		fprintf(stdout, " - %s", g_ast_names[ast->kind]);
	if (ast->kind == EXP_ADD
		|| ast->kind == EXP_SUB
		|| ast->kind == EXP_MUL
		|| ast->kind == EXP_DIV
		|| ast->kind == EXP_MOD)
		put_binop(ast, depth);
}

void	ast_debug(t_ast *ast)
{
	__log(Warning, "Dumping ast");
	inner(ast, 0);
}