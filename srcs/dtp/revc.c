/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:24:40 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/19 16:59:50 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtp.h"

int     socket_receiver(int port)
{
    int     sock;
    int     optval = 1;
    struct protoent     *proto;
    struct sockaddr_in  sin;

    proto = getprotobyname("tcp");
    if (!proto)
    {
        ft_putendl_fd("data sok, proto is null", 2);
        return (-1);
    }
    if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    {
        ft_putendl_fd("data sock, socket creation error", 2);
        return (-1);
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
        ft_putendl_fd("ERROR SERSOCKOPT", 2);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        ft_putendl_fd("data sock, bind error", 2);
        return (-1);
    }
    listen(sock, 40);
    return (sock);
}

int     revc(int s)
{
    int             r;
    int             ds;
    int             sock;
    char            buf[8];
    socklen_t       len;
    struct sockaddr addr;

    if (get_code(s) == 150)
    {
        send_code(s, 4243);
        if ((sock = socket_receiver(4243)) > 0)
        {
            ft_putendl("Socket created");
            if ((ds = accept(sock, &addr, &len)))
            {
                ft_putendl("AFTER ACCEPT");
                while ((r = recv(ds, buf, 7, 0)) > 0)
                {
                    buf[r] = '\0';
                    ft_putstr(buf);
                }
                ft_putendl("END");
                if (get_code(s) == 226)
                {
                    close(sock);
                    close(ds);
                    return (1);
                }
            }
            close(sock);
        } else {
            ft_putendl("error: socket_receiver");
        }
    }
    return (0);
}