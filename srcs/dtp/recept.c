/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recept.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:24:40 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/29 11:14:09 by zadrien          ###   ########.fr       */
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
        perror("bind()");
        ft_putendl_fd("data sock, bind error", 2);
        return (-1);
    }
    listen(sock, 40);
    return (sock);
}

void    get_streame(int dtp, int fd, int print)
{
    int     r;
    char    buf[8];

    while ((r = recv(dtp, buf, 7, 0)) > 0)
    {
        buf[r] = '\0';
        print ? ft_putstr(buf) : write(fd, buf, 7);
    }
    print == 0 ? close(fd) : 1;
}

int     recept(int s, int fd, int print)
{
    int             r;
    int             dtp;
    int             sock;
    socklen_t      len;
    struct sockaddr addr;

    if ((r = get_code(s)) == 150)
    {
        send_code(s, 50042); // CHOOSE BETTER PORT
        if ((sock = socket_receiver(50042)) > 0)
        {
            if ((dtp = accept(sock, &addr, &len)))
            {
                get_streame(dtp, fd, print);
                write(1, "\n", 1);
                close(dtp);
                close(sock);
                if (get_code(s) == 226)
                    return (1);
            }
            close(sock);
        }
    } else if (r == 530)
        ft_putendl_fd("Not logged in.", 2);
    return (0);
}