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

#include "expr_lexer.h"
#include "logging.h"
#include "libstringf.h"
#include "utils.h"
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

static bool __str_to_uint64(const char *str, size_t *dst)
{
	long tmp;

	tmp = 0;
    if (*str == '0' && *(str + 1) == 'x') {
        char *endptr;
        tmp = strtol(str, &endptr, 16);
        str = endptr;
        if (errno == ERANGE
            || tmp > INT_MAX)
        	return (false);
    } else {
        while (isdigit(*str)) {
            tmp *= 10;
            tmp += *(str++) & 0xCF;
            if (tmp > INT_MAX)
                return (false);
        }
    }
	*dst = tmp;
	if (!*str
		|| isspace(*str)
		|| (*str == '+'
			|| *str == '-'
			|| *str == '*'
		)
		|| *str == '('
		|| *str == ')')
		return (true);
	return (false);
}

static bool tokenize_number(t_token **list, char **ptr)
{
	t_token *token = lst_new_token();

	if (!token)
		return (false);
	if (!__str_to_uint64(*ptr, &token->value))
		return (free(token), false);
	if (**ptr == '0' && *(*ptr + 1) == 'x')
		(*ptr)+=2;
	while (**ptr >= '0' && **ptr <= '9')
		(*ptr)++;
	lst_add_token(list, token, TOKEN_VAL);
	return (true);
}


static bool	tokenize_paren(t_token **list, char **ptr, int32_t kind)
{
	t_token *token = lst_new_token();

	if (token && (*ptr)++) {
		lst_add_token(list, token, kind);
		return (true);
	}
	return (false);
}

static bool tokenize_operator(t_token **list, char **ptr)
{
	t_token *token = lst_new_token();

	if (token) {
		switch (**ptr)
		{	
			case '+':	lst_add_token(list, token, TOKEN_ADD); break ;
			case '-':	lst_add_token(list, token, TOKEN_SUB); break ;
			case '*':	lst_add_token(list, token, TOKEN_MUL); break ;
		}
		(*ptr)++;
		return (true);
	}
	return (false);
}

bool token_list_create(t_token **list, const char *in)
{
	char	*ptr;
	t_token *token;

	ptr = (char *)in;
	while (*ptr)
	{
		while (*ptr && isspace(*ptr))
			ptr++;

		if (isdigit(*ptr) 
			&& tokenize_number(list, &ptr)) {
			continue ;

		} else if ((*ptr == '+' || *ptr == '-' || *ptr == '*'
			) && tokenize_operator(list, &ptr)) {
			continue ;

		} else if (*ptr == '('
			&& tokenize_paren(list, &ptr, TOKEN_LPAREN)) {
			continue ;

		} else if (*ptr == ')'
			&& tokenize_paren(list, &ptr, TOKEN_RPAREN)) {
			continue ;

		} else {
			FATAL_ERROR("Unrecognized token: '%s'", ptr);
			return (false);
		}
	}

	token = lst_new_token();
	if (!token)
		return (lst_destroy(list), false);

	lst_add_token(list, token, TOKEN_END);
	return (true);
}
