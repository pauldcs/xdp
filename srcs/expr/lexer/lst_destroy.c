/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:29:25 by pducos            #+#    #+#             */
/*   Updated: 2023/03/21 00:17:26 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr/expr_lexer.h"
#include <stdlib.h>

void	lst_destroy(t_token **token_list)
{
	t_token	*tmp = *token_list;
	t_token	*node = tmp;

	while (node) {
		tmp = node;
		node = node->next;
		free(tmp);
	}	
	*token_list = NULL;
}