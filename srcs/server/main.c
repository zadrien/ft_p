/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 12:16:01 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/05 13:47:42 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void usage(char *str)
{
    ft_putstr_fd(str, 2);
    ft_putendl_fd(" <port>", 2);
    exit(-1);
}

void    init_fork(int cs)
{
    int     r;
    char    buf[1024];

    if (fork() == 0)
    {
        while ((r = read(cs, buf, 1023)) > 0)
        {
            buf[r] = '\0';
            serverPI(buf, cs);
        }
        close(cs);
    }
}

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
    if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1) {
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

int     main(int ac, char **av)
{
    int             cs;
    int             socket;
    unsigned int    len;
    struct sockaddr addr;

    if (ac != 2)
        usage(av[0]);
    socket = init_server(ft_atoi(av[1]));
    while ((cs = accept(socket, &addr, &len)) > 0)
    {
        init_fork(cs);
    }
    return (0);
}