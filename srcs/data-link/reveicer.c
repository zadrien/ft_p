/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reveicer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:24:36 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/18 20:18:14 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <netdb.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
#include "libft.h"

int     com_link(char *addr, char *port)
{
    int                 p;
    int                 sock;
    struct protoent     *proto;
    struct sockaddr_in  sin;

    p = ft_atoi(port);
    if ((proto = getprotobyname("tcp")))
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) != -1)
        {
            ft_putendl_fd("Socket created", 2);
            sin.sin_family = AF_INET;
            sin.sin_port = htons(p);
            sin.sin_addr.s_addr = inet_addr(addr);
            if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
            {
                ft_putendl_fd("Connect error", 2);
                return (-1);
            }
            ft_putendl_fd("Socket connected to server", 2);
            return (sock);
        } else {
            ft_putendl_fd("socket creation error", 2);
        }
    } else {
        ft_putendl_fd("proto is null", 2);
    }
    return (-1);
}

void    send_line(int s, char *str)
{
    send(s, str, ft_strlen(str), 0);
}

int     data_sock(int port)
{
    int     sock;
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
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        ft_putendl_fd("data sock, bind error", 2);
        return (-1);
    }
    listen(sock, 1);
    return (sock);
}
void    wait_res(int s)
{
    int     port = 4200;
    int     sock;
    int     ss;
    int             r;
    char            buf[1024];
    struct sockaddr addr;
    socklen_t       len;

    // envoyer port
    if (recv(s, &r, sizeof(int), 0))
    {
        if (r == 150)
        {
            send(s, &port, sizeof(int), 0);
            // attendre la connection
            if ((sock = data_sock(port)) != -1)
            {
                if ((ss = accept(s, &addr, &len)))
                {
                    ft_putendl("Connect to dtp");
                    ft_putendl("RECV:");
                    while ((r = recv(ss, buf, 1023, 0)))
                    {
                        buf[r] = '\0';
                        ft_putstr(buf);
                    }
                }
            }
        }
    }
}

void    loop(int s)
{
    char    *line;


    while (1)
    {
        ft_putstr_fd("$> ", 2);
        if (get_next_line(0, &line) > 0)
        {
            ft_putendl(line);
            send_line(s, line);
            wait_res(s);
        }
    }
}

int     main(int ac, char **av)
{
    int     sock;

    if (ac != 3)
        return (0);
    if ((sock = com_link(av[1], av[2])) > 0)
    {
        loop(sock);
    }
}