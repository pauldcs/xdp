/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_compose.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:25:41 by pducos            #+#    #+#             */
/*   Updated: 2023/06/10 12:44:06 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr.h"
#include "xleaks.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

# define MICROSTACK_SIZE 2048
static const void	*__stack_a[MICROSTACK_SIZE];
static const void	*__stack_b[MICROSTACK_SIZE];
static size_t	top_a;
static size_t	top_b;

static void __push_a(t_ast *node) {
	if (top_a < MICROSTACK_SIZE - 1)
		__stack_a[++top_a] = node;
}
static void __push_b(t_ast *node) {
	if (top_b < MICROSTACK_SIZE - 1)
		__stack_b[++top_b] = node;
}
static void *__pop_a(void) {
	if (top_a > 0)
		return ((void *)__stack_a[top_a--]);
	return ((void *)0);
}
static void *__pop_b(void) {
	if (top_b > 0) 
		return ((void *)__stack_b[top_b--]);
	return ((void *)0);
}

static int get_token_precedence(t_token *token)
{
	switch (token->kind) {
		case TOKEN_LPAREN: return (0);
		case TOKEN_ADD:    return (1);
		case TOKEN_SUB:    return (1);
		case TOKEN_MUL:    return (2);
		default:           return (0);
	}
}

static int get_node_precedence(t_ast *ast)
{
	switch (ast->kind) {
		case EXP_LPAREN: return (0);
		case EXP_ADD:    return (1);
		case EXP_SUB:    return (1);
		case EXP_MUL:    return (2);
		default:         return (0);
	}
}

static void ast_merge_top(void)
{
	t_ast	*node;

	node = __pop_a();
	node->binop.right = __pop_b();
	node->binop.left = __pop_b();
	__push_b(node);
}

t_ast *ast_compose(t_token *list)
{
	t_token *t;

	t = list;
	top_a = top_b = 0;

	bzero(__stack_a, MICROSTACK_SIZE * sizeof(void *));
	bzero(__stack_b, MICROSTACK_SIZE * sizeof(void *));

	while (t)
	{
		if (t->kind == TOKEN_LPAREN) {
			__push_a(ast_new_operator(t->kind));

		} else if (t->kind == TOKEN_VAL) {
			__push_b(ast_new_value(t->value));

		} else if (t->kind == TOKEN_RPAREN) {
	
			while (top_a
				&& (((t_ast *)__stack_a[top_a])->kind != EXP_LPAREN)) {
				ast_merge_top();
			}

			__pop_a();
			__xfree__((void *)__stack_a[top_a + 1]);
		}
		else
		{
			while (top_a
				&& get_node_precedence((t_ast *)__stack_a[top_a]) >= get_token_precedence(t)) {
				ast_merge_top();
			}
			__push_a(ast_new_operator(t->kind));
		}
		t = t->next;
	}
	while (top_b > 1)
		ast_merge_top();
	
	__xfree__((void *)__stack_a[top_a]);
	return ((t_ast *)__stack_b[top_b]);
}