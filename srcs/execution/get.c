/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 15:53:23 by zadrien           #+#    #+#             */
/*   Updated: 2018/09/30 16:15:41 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void    ft_lget(t_token **lst, int socket)
{
    (void)socket;
    t_token *tmp;
    if ((*lst)->next)
    {
        tmp = (*lst)->next;
        ft_putendl(tmp->str);

    }
}

void    ft_get(t_token **lst, t_usr **usr)
{
    (void)lst;
    (void)usr;
}