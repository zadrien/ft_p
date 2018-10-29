/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:06:53 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/29 10:49:36 by zadrien          ###   ########.fr       */
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
            ft_putendl_fd("Data link: Socket created", 2);
            if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
                ft_putendl_fd("ERROR SERSOCKOPT", 2);
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

int     send_str(int s, char *str)
{
    int     i;
    int     j;
    char    buf[8];

    i = 0;
    j = 0;
    str[i] ? (buf[j++] = str[i++]) : 0;
    while (str[i])
    {
        if (i % 7 == 0)
        {
            buf[8] = '\0';
            send(s, buf, ft_strlen(buf), 0);
            ft_bzero(buf, 8);
            j = 0;
        }
        buf[j++] = str[i++];
    }
    buf[j] = '\0';
    if (buf[0] != '\0')
        send(s, buf, ft_strlen(buf), 0);
    close(s);
    return (226);
}

int    transmission(t_usr *usr, int get, int fd)
{
    int     in;
    int     port;
    int     sock;

    in = 150;    
    send(usr->cs, &in, sizeof(int), 0);
    if ((port = get_code(usr->cs)) != -1)
    {
        ft_putstr("DTP PORT: ");ft_putnbr(port);ft_putendl("");
        if ((sock = prepare_socket(usr, port)) > 0)
        {
            if (get)
                return (sock);
            send_data(sock, fd);
            close(sock);
            ft_putendl_fd("Data link server: End transmission", 2);
            return (1);
        }
    }
    return (-1);
}
