/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:32:36 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/19 15:42:09 by zadrien          ###   ########.fr       */
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

typedef struct      s_usr
{
    int             cs;
    struct in_addr  addr;
    int             password;
    char            *user;
    char            *pwd;
    struct t_trans  *files;
    struct s_usr    *next;
}                   t_usr;

int    ascii_mode(t_usr *usr);
int     revc(int s);
int     get_code(int s);
void    send_code(int s, int code);
#endif