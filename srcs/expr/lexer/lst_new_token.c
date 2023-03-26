/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:29:25 by pducos            #+#    #+#             */
/*   Updated: 2023/03/26 16:57:17 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr/expr_lexer.h"
#include "xmem.h"
#include "xtypes.h"
#include <string.h>

t_token	*lst_new_token(void)
{
	t_token	*token;

	if (!xmem_alloc((ptr_t *)&token, sizeof(t_token)))
		return (NULL);
		
	memset(token, 0, sizeof(t_token));
	return (token);
}
