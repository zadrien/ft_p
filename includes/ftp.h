/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:57:00 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/02 12:57:22 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_H
# define FTP_H

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
# include "login.h"

void    execution(char *str, t_usr **usr);
void    send_msg(int cs, char *msg);
void    ft_env(t_token **arg, t_usr **usr);
int     send_file(int socket, char *file);
int     recv_file(int socket, char  *file);

/*
** Server execution
*/
typedef struct      s_builtin
{
    char            *cmd;
    void             (*f)(t_token**, t_usr **);
}                   t_builtin;

void    ft_get(t_token **lst, t_usr **usr);
void    ft_put(t_token **lst, t_usr **usr);


/*
** Client execution
*/

typedef struct      s_client
{
    char            *cmd;
    void            (*f)(t_token**, int);
}                   t_client;

int     client_exec(char *str, int socket);
void    ft_lls(t_token **lst, int socket);
int     ft_countarg(t_token **lst);
void    ft_lpwd(t_token **lst, int socket);
void    ft_lcd(t_token **lst, int socket);
void    ft_lget(t_token **lst, int socket);
void    ft_lput(t_token **lst, int socket);

#endif