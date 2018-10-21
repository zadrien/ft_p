/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put-server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 15:07:39 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/21 15:32:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int     s_put(t_token **lst, t_usr **usr)
{
    int     fd;
    t_token *tmp;
    t_usr   *us;

    tmp = (*lst)->next;
    us = *usr;
    if ((fd = open(tmp->str, O_APPEND | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
    {
        return (wait_client(us->cs, us->addr, fd, GET));
    }
    return (0);
}