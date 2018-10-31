/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countarg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 12:32:36 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/21 12:32:42 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_countarg(t_token **lst)
{
    int i;
    t_token *tmp;

    i = 0;
    if ((tmp = *lst))
        while (tmp)
        {
            i++;
            tmp = tmp->next;
        }
    return (i);
}