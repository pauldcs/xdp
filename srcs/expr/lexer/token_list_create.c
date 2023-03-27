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

#include "expr.h"
#include "log.h"
#include "utils.h"
#include "xleaks.h"
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

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
		|| (*str == '+' || *str == '-' || *str == '*')
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
		return (__xfree__(token), false);
	while (isdigit(**ptr)
		|| **ptr == 'x'
		|| isxdigit(**ptr))
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
	char	*ptr = (char *)in;
	t_token *token;

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
			__log__(fatal,  "Unrecognized token: '%s'", ptr);
			return (false);
		}
	}

	token = lst_new_token();
	if (!token)
		return (lst_destroy(list), false);

	lst_add_token(list, token, TOKEN_END);
	return (true);
}
