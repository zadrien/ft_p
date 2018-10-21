/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get-server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 11:57:07 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/21 15:17:01 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int     s_get(t_token **lst, t_usr **usr)
{
    int     r;
    int     fd;
    t_token *tmp;
    t_usr   *us;

    r = 0;
    us = *usr;
    tmp = (*lst)->next;
    if ((fd = open(tmp->str, O_RDONLY)))
    {
        r = wait_client(us->cs, us->addr, fd, PUT);
        printf("return wait_client=%d\n", r);
        return (r);
    }
    send_code(us->cs, 550); // file not found
    return (r);
}