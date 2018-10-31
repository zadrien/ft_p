/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:57:00 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 11:39:22 by zadrien          ###   ########.fr       */
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
# include <curses.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <stdlib.h>
#include <dirent.h>

# include "libft.h"

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

typedef struct		s_window
{
	size_t			x;
	size_t			y;
	size_t			winsize;
}					t_window;


typedef struct      s_trans
{
    pid_t           pid;
    char            *filename;
    size_t          fsize;
    size_t          atrans;
    struct t_trans  *next;
}                   t_trans;

# include "user.h"
# include "server.h"
# include "dtp.h"

#endif