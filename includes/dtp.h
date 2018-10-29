/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:32:36 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/29 10:47:18 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DTP_H
# define DTP_H

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

enum print {
    NONE = 0,
    PRINT = 1,
    GET = 2,
    PUT = 0
};

typedef struct      s_usr
{
    int             cs;
    struct in_addr  addr;
    int             password;
    char            *user;
    char            *home;
    char            *pwd;
    struct t_trans  *files;
    struct s_usr    *next;
}                   t_usr;

int     transmission(t_usr *usr, int get, int fd);
int     get_code(int s);
void    send_code(int s, int code);
int     recept(int s, int fd, int print);
int     get_port(int s);
int     connect_socket(struct in_addr addr, int port);
int     listen_socket(int port);
int     accept_socket(int sock);
int     send_str(int s, char *str);

/**
 * USER-DTP
*/
int     get_stream(int s, int fd, int print);
int     put_stream(int s, int fd);
int     handle_stream(int s, int fd, int print, int mode);
int     wait_server(int s, int fd, int print, int mode);

/**
 * SERVER-DTP
*/
int     handle_client(int s, int fd, int mode);
int     wait_client(int s, struct in_addr addr, int fd, int mode);

#endif