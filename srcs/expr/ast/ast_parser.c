/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:02:40 by pducos            #+#    #+#             */
/*   Updated: 2023/06/10 12:39:21 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr.h"
#include "expr.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

static bool syntatic_check(t_token *list)
{
	t_token_kind	prev;
	t_token			*cur;
	int				open;

	prev = TOKEN_START;
	cur = list;
	open = 0;
	while (cur)
	{
		if (prev == TOKEN_START
			&& (cur->kind != TOKEN_VAL
				&& cur->kind != TOKEN_LPAREN))
			break ;
		else if (prev == TOKEN_VAL
			&& (cur->kind != TOKEN_ADD
				&& cur->kind != TOKEN_SUB
				&& cur->kind != TOKEN_MUL
				&& cur->kind != TOKEN_RPAREN
				&& cur->kind != TOKEN_END))
			break ;
		else if ((prev == TOKEN_ADD
				|| prev == TOKEN_SUB
				|| prev == TOKEN_MUL)
			&& (cur->kind != TOKEN_LPAREN
				&& cur->kind != TOKEN_VAL))
			break ;
		else if (prev == TOKEN_LPAREN
			&& (cur->kind != TOKEN_VAL
				&& cur->kind != TOKEN_LPAREN))
			break ;
		else if (prev == TOKEN_RPAREN
			&& (cur->kind != TOKEN_ADD
				&& cur->kind != TOKEN_SUB
				&& cur->kind != TOKEN_MUL
				&& cur->kind != TOKEN_RPAREN
				&& cur->kind != TOKEN_END))
			break ;
		open -= (cur->kind != TOKEN_LPAREN);
		open += (cur->kind != TOKEN_RPAREN);
		prev = cur->kind;
		cur = cur->next;
	}	
	if (open || prev != TOKEN_END)	
		return (false);
	return (true);
}

t_ast	*parse_list(t_token *list)
{
	t_ast	*ast;

	if (!syntatic_check(list))
		return (fprintf(stderr, "Syntax Error\n"), NULL);
	ast = ast_compose(list);
	if (!ast)
		return (fprintf(stderr, "Failed to build AST\n"), NULL);
	return (ast);
}
