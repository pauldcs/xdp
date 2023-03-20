/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:25:41 by pducos            #+#    #+#             */
/*   Updated: 2022/11/13 15:03:58 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

# define VSTACK_SIZE 1024
static const void	*__stack_a[VSTACK_SIZE];
static const void	*__stack_b[VSTACK_SIZE];
static size_t	top_a;
static size_t	top_b;

static void
__push_a(t_ast *node)
{ if (top_a < VSTACK_SIZE - 1)
		__stack_a[++top_a] = node;
}
static void
__push_b(t_ast *node)
{ if (top_b < VSTACK_SIZE - 1)
		__stack_b[++top_b] = node;
}
static void *
__pop_a(void)
{ if (top_a > 0)
		return ((void *)__stack_a[top_a--]);
	return ((void *)0);
}
static void *
__pop_b(void)
{ if (top_b > 0)
		return ((void *)__stack_b[top_b--]);
	return ((void *)0);
}

static int get_token_p(t_token *token)
{
	if (token->kind == TOKEN_LPAREN)
		return (0);
	if (token->kind == TOKEN_ADD
		|| token->kind == TOKEN_SUB)
		return (1);
	if (token->kind == TOKEN_MUL
		|| token->kind == TOKEN_DIV
		|| token->kind == TOKEN_MOD)
		return (2);
	return (0);
}

static int get_ast_p(t_ast *ast)
{
	if (ast->kind == EXP_LPAREN)
		return (0);
	if (ast->kind == EXP_ADD
		|| ast->kind == EXP_SUB)
		return (1);
	if (ast->kind == EXP_MUL
		|| ast->kind == EXP_DIV
		|| ast->kind == EXP_MOD)
		return (2);
	return (0);	
}

static void merge_top(void)
{
	t_ast	*node;

	node = __pop_a();
	node->binop.right = __pop_b();
	node->binop.left = __pop_b();
	__push_b(node);
}

t_ast *ast_create(t_token *list)
{
	t_token *t;

	t = list;
	top_a = 0;
	top_b = 0;
	memset(__stack_a, 0x00, VSTACK_SIZE * sizeof(void *));
	memset(__stack_b, 0x00, VSTACK_SIZE * sizeof(void *));
	while (t)
	{
		if (t->kind == TOKEN_LPAREN)
			__push_a(ast_new_op(t->kind));
		else if (t->kind == TOKEN_VAL)
			__push_b(ast_new_val(t->value));
		else if (t->kind == TOKEN_RPAREN)
		{
			while (top_a
				&& (((t_ast *)__stack_a[top_a])->kind != EXP_LPAREN))
				merge_top();
			__pop_a();
		}
		else
		{
			while (top_a
				&& get_ast_p((t_ast *)__stack_a[top_a]) >= get_token_p(t))
				merge_top();
			__push_a(ast_new_op(t->kind));
		}
		t = t->next;
	}
	while (top_b > 1)
		merge_top();
	return ((t_ast *)__stack_b[top_b]);
}