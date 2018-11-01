/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp-utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:14:00 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 16:12:17 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int    get_code(int s)
{
    int     r;

    r = 0;
    if (recv(s, &r, sizeof(int), 0) == -1)
        perror("recv");
    printf("get_code(s) =  %d\n", r);    
    return (r);
}

void    send_code(int s, int code)
{
    if (send(s, &code, sizeof(int), 0) == -1)
        perror("send()");
}

int     get_port(int s)
{
    int     port;

    port = get_code(s);
    return (port);
}

int     connect_socket(struct in_addr addr, int port)
{
    int                 sock;
    int                 optval = 1;
    struct protoent     *proto;
    struct sockaddr_in  sin;

    if ((proto = getprotobyname("tcp")))
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) != -1)
        {
            ft_putendl_fd("Data link: Socket created", 2);
            if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
                ft_putendl_fd("ERROR SERSOCKOPT", 2);
            sin.sin_family = AF_INET;
            sin.sin_port = htons(port);
            sin.sin_addr = addr;
            if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
            {
                perror("connect: ");
                ft_putendl_fd("Data link server: Connect error", 2);
                return (-1);
            }
            ft_putendl_fd("Data link server: Connect success", 2);
            return (sock);
        }
    }
    return (0);
}

