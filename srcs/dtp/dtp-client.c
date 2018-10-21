/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp-client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 17:51:53 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/21 16:21:44 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtp.h"

int     handle_stream(int s, int fd, int print, int mode)
{
    int     r;

    r = 0;
    if (mode == GET)
    {
        r = get_stream(s, fd, print);
    } else {
        // envoyer au serveur
        ft_putendl("MODE PUT");
        printf("%d\n", fd);
        r = put_stream(s, fd);
    }
    
    return (r);
}

int     wait_server(int s, int fd, int print, int mode)
{
    int     cs;
    int     port;
    int     sock;
    socklen_t           len;
    struct sockaddr     addr;

    port = 50042;
    if (get_code(s) == 150) // can cause bug
    {
        send_code(s, port);
        if ((sock = listen_socket(port)) > 0)
        {
            ft_putendl("Waiting for server to connect");
            if ((cs = accept(sock, &addr, &len)))
            { // begin transfer
                ft_putendl("IN");
                handle_stream(cs, fd, print, mode);
                if (get_code(s) == 226)
                {
                    ft_putendl("Close sock");
                    close(sock);
                    return (1);
                }
            } else {
                ft_putendl("Error");
            }
            close(sock);
        }
    }
    return (0);
}