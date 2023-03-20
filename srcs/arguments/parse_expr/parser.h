/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:52:01 by pducos            #+#    #+#             */
/*   Updated: 2022/11/28 08:10:33 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
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
void	ast_display(t_ast *ast);
t_ast	*ast_new_val(int value);
t_ast	*ast_new_op(t_token_kind kind);
void	ast_display(t_ast *ast);
size_t	ast_solve(t_ast *ast);

#endif