/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 15:53:36 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/02 13:10:10 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void    ft_lput(t_token **lst, int socket)
{
    (void)socket;
    int     r;
    char    buf[1024];
    // char    *str;
    t_token *tmp;

    if ((*lst)->next)
    {
        tmp = (*lst)->next;
        // if ()
        ft_putendl(tmp->str);
        // ft_putendl(ft_strrchr(tmp->str, '/'));
        send(socket, "put", 3, 0);
        if ((r = recv(socket, buf, 1023, 0)) > 0)
        {
            buf[r]= '\0';
            if (!ft_strcmp("IN", buf))
            {
                ft_putendl("SEND FILE NAME");
                send(socket,  tmp->str, ft_strlen(tmp->str), 0);
                if ((r = recv(socket, buf, 1023, 0)) > 0)
                {
                    buf[r] = '\0';
                    if (!ft_strcmp("FILE CREATED", buf))
                    {
                        ft_putendl("FILE CREATED");
                        ft_putendl("PROCEED TRANSFERT");
                        if (send_file(socket, tmp->str))
                            ft_putendl("TRANSFERT DONE");
                    }
                }
            }
        }

    }
}

void    ft_put(t_token **lst, t_usr **usr)
{
    (void)lst;
    int     r;
    char    buf[1024];
    t_usr   *tmp;

    ft_putendl("IN PUT SERVER");
    if (*usr)
    {
        tmp = *usr;
        send(tmp->cs, "IN", 2, 0);
        if ((r = recv(tmp->cs, buf, 1023, 0)) > 0)
        {
            buf[r] = '\0';
            ft_putstr("server receive file name of: ");
            ft_putendl(buf);
            recv_file(tmp->cs, buf);
        }
    }
    // say i'm in the functon
    
    // reveice the name of the file and create it

    // initiate the file transfert to the server

}