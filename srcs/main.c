/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:56:09 by zadrien           #+#    #+#             */
/*   Updated: 2018/09/28 14:19:52 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"


void usage(char *str)
{
    ft_putstr_fd(str, 2);
    ft_putendl_fd(" <port>", 2);
    exit(-1);
}


int     create_server(int port)
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

void     send_msg(int cs, char *msg) 
{
    send(cs, msg, ft_strlen(msg), 0);
}

int     main(int ac, char **av)
{
    int             cs;
    int             port;
    int             socket;
    t_usr           *tmp;
    t_usr           *usr = NULL;
    unsigned int    len;
    struct sockaddr caddr;

    
    if (ac != 2)
        usage(av[0]);
        port = ft_atoi(av[1]);
    socket = create_server(port);
    while ((cs = accept(socket, &caddr, &len)) > 0)
    {
        if (usr)
        {
            tmp = usr;
            while (tmp)
            {
                ft_env(NULL, &tmp);
                tmp = tmp->next;
            }
        }
        finding_usr(&usr, cs);
    }


}

// int     main(int ac, char **av, char **envp)
// {
//     int             port;
//     int             socket;
//     int             cs;
//     int             r;
//     unsigned int    len;
//     struct sockaddr caddr;
//     char            buf[1024];
//     char            *suc = "SUCCESS";
//     t_env           *env;

//     env = new_env(envp);
//     ft_putendl("init env");
//     if (ac != 2 && env)
//         usage(av[0]);
//     port = ft_atoi(av[1]);
//     socket = create_server(port);
//     while ((cs = accept(socket, &caddr, &len)) > 0) {
//         if (fork() == 0)
//         {
//             ft_putendl("new client is connected");
//             while ((r = read(cs, buf, 1023)) > 0)
//             {
//                 execution(buf, &env);
//                 ft_bzero(buf, 1024);
//                 send(cs, suc, ft_strlen(suc), 0);
//             }
//             ft_putendl("user is disconnected");
//             close(cs);
//             exit(0);
//         }
//     }    
//     close(cs);
//     close(socket);
//     return (0);
// }