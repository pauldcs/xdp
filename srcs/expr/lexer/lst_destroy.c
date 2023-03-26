/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:29:25 by pducos            #+#    #+#             */
/*   Updated: 2023/03/26 16:51:40 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr/expr_lexer.h"
#include "xmem.h"

void	lst_destroy(t_token **token_list)
{
	t_token	*tmp = *token_list;
	t_token	*node = tmp;

	while (node) {
		tmp = node;
		node = node->next;
		xmem_free(tmp);
	}	
	*token_list = NULL;
}