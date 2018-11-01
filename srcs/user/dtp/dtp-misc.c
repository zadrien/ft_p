/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp-misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:09:04 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/01 10:31:33 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int    get_code(int s)
{
    int     r;

    r = 0;
    if (recv(s, &r, sizeof(int), 0) == -1)
        perror("recv");
    return (r);
}

void    send_code(int s, int code)
{
    if (send(s, &code, sizeof(int), 0) == -1)
        perror("send()");
}

int     listen_socket(int port)
{
    int                 sock;
    int                 optval;
    struct protoent     *proto;
    struct sockaddr_in  sin;

    optval = 1;
    if ((proto  = getprotobyname("tcp")))
        if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)))
        {
            if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
                return (-1);
            sin.sin_family = AF_INET;
            sin.sin_port = htons(port);
            sin.sin_addr.s_addr = htonl(INADDR_ANY);
            if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
                return (-2);
            listen(sock, 40);
            return (sock);
        }
    return (0);
}

int     accept_socket(int sock)
{
    int                 cs;
    socklen_t           len;
    struct sockaddr_in     addr;

    if ((cs = accept(sock, (struct sockaddr*)&addr, &len)))
        return (cs);
    return (0);
}