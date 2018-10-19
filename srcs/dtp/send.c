/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:06:53 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/19 16:59:40 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtp.h"

int     prepare_socket(t_usr *usr, int port)
{
    int                 sock;
    int                 optval = 1;
    struct protoent     *proto;
    struct sockaddr_in  sin;

    if ((proto = getprotobyname("tcp")))
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) != -1)
        {
            if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
                ft_putendl_fd("ERROR SERSOCKOPT", 2);
            ft_putendl_fd("Data link: Socket created", 2);
            sin.sin_family = AF_INET;
            sin.sin_port = htons(port);
            sin.sin_addr = usr->addr;
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

void    send_data(int s, int fd)
{
    int     r;
    char    buf[8];

    while ((r = read(fd, buf, 7)) > 0)
    {
        buf[r] = '\0';
        send(s, buf, ft_strlen(buf), 0);
    }
    close(fd);
}

int    ascii_mode(t_usr *usr)
{
    int                 port;
    int                 sock;
    int    in = 150;
    
    ft_putnbr(usr->cs);ft_putendl("");
    send(usr->cs, &in, sizeof(int), 0);
    send_code(usr->cs, 150); // say client im in
    port = get_code(usr->cs);
    ft_putstr("DTP PORT: ");ft_putnbr(port);ft_putendl("");

    if ((sock = prepare_socket(usr, port)))
    {
        return (sock);
        // send_data(sock, fd);
        close(sock);
        ft_putendl_fd("Data link server: End transmission", 2);
    }
    return (-1);
}