/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:32:39 by pducos            #+#    #+#             */
/*   Updated: 2023/03/20 21:18:51 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "logging.h"
#include "libstringf.h"
#include "expr_parser.h"

static void	inner(t_ast *ast, size_t depth);

static const char	*g_ast_names[] = {
	"lparen", "rparen", "val",
	"operator='MUL'", "operator='ADD'", "operator='SUB'"
};

static void	put_binop(t_ast *ast, size_t depth)
{
	putstr("\n");
	inner(ast->binop.left, depth + 1);
	inner(ast->binop.right, depth + 1);
}

static void	inner(t_ast *ast, size_t depth)
{
	size_t	i;

	i = 0;
	while (i++ < depth)
		putstr("%4s", "");
	if (ast->kind == EXP_VAL)
		putstr(" - value='%d'\n", ast->value);
	else
		putstr(" - %s", g_ast_names[ast->kind]);
	if (ast->kind == EXP_ADD
		|| ast->kind == EXP_SUB
		|| ast->kind == EXP_MUL
		|| ast->kind == EXP_DIV
		|| ast->kind == EXP_MOD)
		put_binop(ast, depth);
}

void	ast_debug(t_ast *ast)
{
	setbuf(stdout, NULL);
	putstr(" . Root\n");
	inner(ast, 0);
}