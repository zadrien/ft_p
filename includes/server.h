/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:34:02 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/10 11:37:46 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

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

# include "libft.h"

typedef struct      s_usr
{
    int             cs;
    char            *user;
    int             password;
    char            *pwd;
    struct t_trans  *files;
    struct s_usr    *next;
}                   t_usr;

typedef struct      s_trans
{
    pid_t           pid;
    char            *filename;
    size_t          fsize;
    size_t          atrans;
    struct t_trans  *next;
}                   t_trans;

void    serverPI(char *str, t_usr **usr, int cs);

int     ft_user(t_token **lst, t_usr **usr, int cs);
int     ft_password(t_token **lst, t_usr **usr, int cs);
int     ft_logout(t_token **lst, t_usr **usr, int cs);

int     ft_list(t_token **lst, t_usr **usr, int cs);

int     user_reply(int code, char *msg, int cs);
int     check_user(t_usr **usr, int cs);
int     verify_auth(char *str);
int     ft_countarg(t_token **lst);

#endif