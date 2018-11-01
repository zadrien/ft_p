/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 12:16:01 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/01 09:20:54 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void usage(char *str)
{
    ft_putstr_fd(str, 2);
    ft_putendl_fd(" <port>", 2);
    exit(-1);
}

t_usr    *init_usr(int cs, struct sockaddr_in addr)
{
    t_usr   *tmp;
    
    if (!(tmp = (t_usr*)malloc(sizeof(t_usr))))
        return (NULL);
    tmp->cs = cs;
    tmp->addr = addr.sin_addr;
    tmp->user = NULL;
    tmp->password = 0;
    tmp->pwd = NULL;
    tmp->home = NULL;
    tmp->files = NULL;
    tmp->next = NULL;
    return (tmp);
}

void    client_session(int cs, struct sockaddr_in addr)
{
    int             r;
    char            buf[1024];
    t_usr           *usr;

    if ((usr = init_usr(cs, addr)))
    {
        send_code(cs, 220);
        while ((r = read(cs, buf, 1023)) > 0)
        {
            buf[r] = '\0';
            ft_putendl(buf);
            serverPI(buf, &usr, cs);
        }
        ft_putendl_fd("Client quit the server", 2);
    } else
        send_code(cs, 421);
    close(cs);
}

void    init_fork(int cs, struct sockaddr_in addr)
{
    if (fork() == 0)
    {
        if (!chdir("./usr"))
        {
            print_msg("In usr directory", GREEN, 2);
            client_session(cs, addr);
        }
        exit(EXIT_FAILURE);
    }
}

int     init_server(int port)
{
    int     sock;
    int             optval = 1;
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
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
                ft_putendl_fd("ERROR SERSOCKOPT", 2);
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
    struct sockaddr_in addr;

    if (ac != 2)
        usage(av[0]);
    socket = init_server(ft_atoi(av[1]));
    while ((cs = accept(socket, (struct sockaddr*)&addr, &len)) > 0)
    {
        ft_putendl("New user");
        init_fork(cs, addr);
    }
    return (0);
}