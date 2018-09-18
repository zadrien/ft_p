/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:56:09 by zadrien           #+#    #+#             */
/*   Updated: 2018/09/18 17:34:11 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ftp.h"


void usage(char *str)
{
    ft_putstr_fd(str, 2);
    ft_putendl_fd(" <port>", 2);
    exit(-1);
}


int     create_socket(int port)
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
    int             port;
    int             socket;
    int             cs;
    int             r;
    unsigned int    len;
    struct sockaddr caddr;
    char            buf[1024];
    
    if (ac != 2)
        usage(av[0]);
    port = ft_atoi(av[1]);
    socket = create_socket(port);
    while ((cs = accept(socket, &caddr, &len)) > 0) {
        if (fork() == 0)
        {
            ft_putendl("new client is connected");
            while ((r = read(cs, buf, 1023)) > 0)
            {
                ft_putstr("client send: ");
                ft_putstr(buf);
                ft_bzero(buf, 1024);
            }
            close(cs);
            exit(0);
        }
    }

    
    close(cs);
    close(socket);
    return (0);
}