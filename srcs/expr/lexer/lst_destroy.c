/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:29:25 by pducos            #+#    #+#             */
/*   Updated: 2023/03/26 22:51:01 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr.h"
#include "xmem.h"
#include <stdlib.h>

void	lst_destroy(t_token **token_list)
{
	t_token	*tmp = *token_list;
	t_token	*node = tmp;

	while (node) {
		tmp = node;
		node = node->next;
		__xfree__(tmp);
	}	
	*token_list = NULL;
}