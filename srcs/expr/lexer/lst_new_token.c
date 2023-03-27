/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:29:25 by pducos            #+#    #+#             */
/*   Updated: 2023/03/27 23:08:10 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr.h"
#include "xleaks.h"
#include "xtypes.h"
#include <string.h>
#include <stdlib.h>

t_token	*lst_new_token(void)
{
	t_token	*token = __xmalloc__(sizeof(t_token));

	if (!token)
		return (NULL);
		
	memset(token, 0, sizeof(t_token));
	return (token);
}
