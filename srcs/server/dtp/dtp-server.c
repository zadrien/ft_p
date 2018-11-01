/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp-server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 17:52:01 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/01 11:06:40 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int     send_info(int fd, int cs)
{
    struct stat buf;

    if (!fstat(fd, &buf))
        send(cs, &buf.st_size, sizeof(buf.st_size), 0);
    return (1);
}

int     handle_client(int s, int fd, int mode)
{
    int     r;

    r = -1;
    if (mode == GET)
    { // stocker dans un fichier
        r = get_stream(s, fd, NONE, NONE);
    } else {
        send_info(fd, s); // handle error
        r = put_stream(s, fd);
    }
    return (r);
}

int     get_socket(t_usr *usr)
{
    int     in;
    int     sock;
    int     port;

    in = 150;
    send(usr->cs, &in, sizeof(int), 0);
    if ((port = get_port(usr->cs)))
    {
        if ((sock = connect_socket(usr->addr, port)) > 0)
            return (sock);
    }
    return (425);
}

int     wait_client(int s, struct in_addr addr, int fd, int mode)
{
    int     in;
    int     port;
    int     sock;

    in = 150;
    send(s, &in, sizeof(int), 0);
    if ((port = get_port(s)))
    {
        printf("DTP PORT = %d\n", port);
        if ((sock = connect_socket(addr, port)) > 0)
        {// demarrer transfert
            handle_client(sock, fd, mode);
            // send_code(s, 226);
            ft_putendl("close socket");
            close(sock);
            return (226);
        }
    }
    return (425); // Can't open data connection
}