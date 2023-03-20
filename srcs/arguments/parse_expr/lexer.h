/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:10:35 by pducos            #+#    #+#             */
/*   Updated: 2022/11/28 08:09:11 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>

typedef enum e_token_kind
{
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_VAL,
	TOKEN_MUL,
	TOKEN_DIV,
	TOKEN_MOD,
	TOKEN_ADD,
	TOKEN_SUB,
	TOKEN_START,
	TOKEN_END
}	t_token_kind;

typedef struct s_token {
	t_token_kind	kind;
	int				value;
	struct s_token	*next;
}	t_token;

bool	is_cparen(char c);
bool	is_num(char c);
bool	is_op(char c);
bool	is_oparen(char c);
bool	is_space(char c);

bool	toklist_build(t_token **list, const char *in);

t_token	*lst_newtok(void);
void	lst_addtok(t_token **toklist, t_token *tok, t_token_kind kind);
void	lst_destroy(t_token **toklist);
size_t	lst_size(t_token *lst);

#endif