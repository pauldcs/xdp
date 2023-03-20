/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:52:01 by pducos            #+#    #+#             */
/*   Updated: 2023/03/20 15:47:28 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EXPR_PARSER_H__
# define __EXPR_PARSER_H__

# include "expr_lexer.h"
# include <stdbool.h>

typedef enum e_exp_kind
{
	EXP_LPAREN,
	EXP_RPAREN,
	EXP_VAL,
	EXP_MUL,
	EXP_ADD,
	EXP_SUB,
	EXP_DIV,
	EXP_MOD,
}	t_exp_kind;

typedef struct s_ast t_ast;

struct s_ast
{
	t_exp_kind	kind;
	union {
		int		value;
		struct	s_binop {
			t_ast	*left;
			t_ast	*right;
		}	binop;
	};
};

t_ast	*parser(t_token *list);
t_ast	*ast_create(t_token *tokenlist);
t_ast	*ast_new_value(int value);
t_ast	*ast_new_operator(t_token_kind kind);
void	ast_debug(t_ast *ast);
size_t	ast_solve(t_ast *ast);

#endif /* __EXPR_PARSER_H__ */