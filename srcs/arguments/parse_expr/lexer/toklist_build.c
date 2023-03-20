/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:47:45 by pducos            #+#    #+#             */
/*   Updated: 2022/11/09 01:20:58 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

static char *str_to_int(char *str, int *result)
{
	int		sign;
	char	*ret;
	long	tmp;

	tmp = 0;
	sign = 0;
	if (*str == '-')
	{
		sign++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tmp *= 10;
		tmp += *(str++) & 0xCF;
		if (tmp - sign > INT_MAX)
			return (NULL);
	}
	if (sign)
		tmp *= -1;
	*result = (int)tmp;
	ret = str;
	return (ret);
}

static bool tokenize_num(t_token **list, char **ptr)
{
	t_token *tok;
	char	*tmp;
	
	tok = lst_newtok();
	if (!tok)
		return (false);
	tmp = str_to_int(*ptr, &tok->value);
	if (!tmp)
		return (free(tok), false);
	*ptr = tmp;
	lst_addtok(list, tok, TOKEN_VAL);
	return (true);
}


static bool	tokenize_paren(t_token **list, char **ptr, int32_t kind)
{
	t_token *tok;

	tok = lst_newtok();
	if (tok && (*ptr)++)
	{
		lst_addtok(list, tok, kind);
		return (true);
	}
	return (false);
}

static bool tokenize_op(t_token **list, char **ptr)
{
	t_token *tok;

	tok = lst_newtok();
	if (tok)
	{
		if (**ptr == '+')		lst_addtok(list, tok, TOKEN_ADD);
		else if (**ptr == '-')	lst_addtok(list, tok, TOKEN_SUB);
		else if (**ptr == '*')	lst_addtok(list, tok, TOKEN_MUL);
		else if (**ptr == '/')	lst_addtok(list, tok, TOKEN_DIV);
		else if (**ptr == '%')	lst_addtok(list, tok, TOKEN_MOD);
		(*ptr)++;
		return (true);
	}
	return (false);
}

bool toklist_build(t_token **list, const char *in)
{
	char	*ptr;
	t_token *tok;

	ptr = (char *)in;
	while (*ptr)
	{
		while (*ptr && is_space(*ptr))
			ptr++;
		if ((is_num(*ptr) || (*ptr == '-' && is_num(*(ptr + 1))))
			&& tokenize_num(list, &ptr))
			continue ;
		if (is_op(*ptr) && tokenize_op(list, &ptr))
			continue ;
		if (is_oparen(*ptr) && tokenize_paren(list, &ptr, TOKEN_LPAREN))
			continue ;
		if (is_cparen(*ptr) && tokenize_paren(list, &ptr, TOKEN_RPAREN))
			continue ;
		return (printf("Unrecognized character: '%c'\n", *ptr),
			lst_destroy(list),
			false);
	}
	tok = lst_newtok();
	if (!tok)
		return (lst_destroy(list), false);
	lst_addtok(list, tok, TOKEN_END);
	return (true);
}
