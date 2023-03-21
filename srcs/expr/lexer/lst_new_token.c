/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:29:25 by pducos            #+#    #+#             */
/*   Updated: 2023/03/21 00:17:32 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr/expr_lexer.h"
#include <string.h>
#include <stdlib.h>

t_token	*lst_new_token(void)
{
	t_token	*token = malloc(sizeof(t_token));

	if (!token)
		return (NULL);
		
	memset(token, 0, sizeof(t_token));
	return (token);
}