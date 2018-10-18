/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:24:23 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/18 20:21:20 by zadrien          ###   ########.fr       */
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

int     init_server(int port)
{
    int     sock;
    struct protoent *proto;
    struct sockaddr_in  sin;

    proto = getprotobyname("tcp");
    if (!proto) {
        ft_putendl_fd("proto is null", 2);
        return (-1);
    }
    if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1) {
        ft_putendl_fd("socket creation error", 2);
        return (-1);
    }
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (const struct sockaddr *)&sin ,sizeof(sin)) == -1) {
        ft_putendl_fd("bind error", 2);
        return (-1);
    }
    listen(sock ,42);
    return (sock);
}

void    send_data(int s)
{
    int     r;
    int     fd;
    char    buf[1024];

    if ((fd = open("file", O_RDONLY)))
    {
        while ((r = read(fd, buf, 1023)) > 0)
        {
            buf[r] = '\0';
            send(s, buf, ft_strlen(buf), 0);
        }
        close(fd);
        close(s);
        ft_putendl_fd("Data link server: End transmission", 2);        
    }
}

void    data_link(int cs)
{
    int     port;
    int     sock;
    struct protoent     *proto;
    struct sockaddr_in  sin;
    struct sockaddr     host;
    socklen_t           len;


    port = 150;
    send(cs, &port, sizeof(int), 0);


    recv(cs, &port, sizeof(int), 0);
    printf("DTP PORT: %d\n", port);

    if (getsockname(cs, &host, &len) == -1)
    {
        ft_putendl_fd("can't get socket details", 2);
        return ;
    }
    if ((proto = getprotobyname("tcp")))
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) != -1)
        {
            ft_putendl_fd("Data linkL: Socket created", 2);
            sin.sin_family = AF_INET;
            sin.sin_port = htons(port);
            sin.sin_addr.s_addr = inet_addr(host.sa_data);
            if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
            {
                ft_putendl_fd("Data link server: Connect error", 2);
                return ;
            }
            ft_putendl_fd("Data link server: Connect success", 2);
            send_data(sock);
            return ;
        }
    }
    ft_putendl_fd("Data link server: FAILURE", 2);
}

void    loop(int cs, struct sockaddr addr)
{
    int     r;
    char    buf[1024];

    if ((r = recv(cs, buf, 1023, 0)))
    {
        buf[r] = '\0';
        ft_putendl(buf);
        if (!ft_strcmp(buf, "ls"))
        {
            ft_putendl("LS FOUND");
            data_link(cs);
        }
        close(cs);
    }
}

int     main(int ac, char **av)
{
    int cs;
    int sock;
    int port;
    struct sockaddr addr;
    socklen_t       len;

    if (ac != 2)
        return (0);
    port = ft_atoi(av[1]);
    if (sock = init_server(port))
    {
        if (cs = accept(sock, &addr, &len))
        {
            ft_putendl_fd("New user connected", 2);
            loop(cs, addr);
        }
    }
}