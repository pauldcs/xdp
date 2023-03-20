/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 03:29:59 by pducos            #+#    #+#             */
/*   Updated: 2022/11/13 14:37:54 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stddef.h>

size_t	lst_size(t_token *lst)
{
        size_t  size;
        t_token *tmp;

        size = 0;
        if (lst)
        {
                tmp = lst;
                size++;
                while (tmp->next)
                {
                        tmp = tmp->next;
                        size++;
                }
        }
        return (size);
}