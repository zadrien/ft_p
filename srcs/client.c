/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:56:09 by zadrien           #+#    #+#             */
/*   Updated: 2018/09/30 16:06:26 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ftp.h"


void usage(char *str)
{
    ft_putstr_fd(str, 2);
    ft_putendl_fd(" <addr> <port>", 2);
    exit(-1);
}


int     create_client(char *addr, int port)
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
    sin.sin_addr.s_addr = inet_addr(addr);
    if (connect(sock, (const struct sockaddr *)&sin ,sizeof(sin)) == -1) {
        ft_putendl_fd("Connect error", 2);
        return (-1);
    }
    return (sock);
}

int     identification(int socket)
{
    int     r;
    char    *line;
    char    str[1024];

    ft_putstr("Nom d'utilisateur: ");
    if (get_next_line(1, &line) > 0)
    {
        write(socket, line, ft_strlen(line));
    }
    if ((r = recv(socket, str, 1023, 0)) <= 0)
    {
        ft_putendl_fd("identification recv error2", 2);
        return (0);
    }
    str[r] = '\0';
    if (!(ft_strcmp(str, "SUCCESS")))
        return (1);
    return (0);
}

char    *cmd_line()
{
    char    *line;

    ft_putstr_fd("$> ", 2);
    if (get_next_line(1, &line) > 0)
        return (line);
    return (NULL);
}

int     main(int ac, char **av)
{
    int     port;
    int     socket;
    char    *str;

    if (ac != 3)
        usage(av[0]);
    port = ft_atoi(av[2]);
    socket = create_client(av[1], port);
    if (identification(socket))
    {
        while (1)
        {
            str = cmd_line();
            client_exec(str, socket);
            ft_strdel(&str);
        }
    }
    close(socket);
    return (0);
}

// int     main(int ac, char **av)
// {
//     int             port;
//     int             socket;
//     int             r;
//     char            *str;
//     char            buf[1024];

//     if (ac != 3)
//         usage(av[0]);
//     port = ft_atoi(av[2]);
//     socket = create_client(av[1], port);
//     if (identification(socket))
//     {
        
//         ft_putstr_fd("$> ", 2);
//         while (get_next_line(1, &str) > 0)
//         {
//             if (!ft_strcmp(str, "quit"))
//             {
//                 free(str);
//                 break ;
//             }
//             write(socket, str, ft_strlen(str));
//             if ((r = recv(socket, buf, 1023 , 0)) <= 0)
//             {
//                 ft_putendl_fd("recv error", 2);
//                 break ;
//             }
//             buf[r] = '\0';
//             ft_putendl(buf);
            
//             ft_putstr_fd("$> ", 2);        
//         }
//     }
//     close(socket);
//     return (0);
// }