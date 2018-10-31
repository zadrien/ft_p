/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get-server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 11:57:07 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 16:42:31 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"



int     s_get(t_token **lst, t_usr **usr)
{
    int     r;
    int     in;
    int     fd;
    t_token *tmp;
    t_usr   *us;

    r = 0;
    in = 150;
    us = *usr;
    tmp = (*lst)->next;
    if ((fd = open(tmp->str, O_RDONLY)) > 0)
    {
        send(us->cs, &in, sizeof(int), 0);
        r = wait_client(us->cs, us->addr, fd, PUT);
        printf("return wait_client=%d\n", r);
        return (r);
    }
    return (550);
}