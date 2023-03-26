/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 03:29:59 by pducos            #+#    #+#             */
/*   Updated: 2023/03/26 20:08:20 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expr.h"
#include <stddef.h>

size_t	lst_size(t_token *lst)
{
        size_t  size;
        t_token *tmp;

        if (lst) {
                tmp = lst;
                size = 1;
                while (tmp->next) {
                        tmp = tmp->next;
                        ++size;
                }
                return (size);
        }
        return (0);
}