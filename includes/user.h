/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:17:40 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/20 15:17:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_H
# define USER_H

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
# include "dtp.h"

int     userPI(char *str, int s);
int     com_link(char *addr, char *port);
int     ft_lls(t_token **lst, int socket);
int     ft_lpwd(t_token **lst, int socket);
int     ft_lcd(t_token **lst, int socket);

char    *ft_struct(char *cmd, t_token **arg);
#endif