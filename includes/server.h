/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:34:02 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 16:31:46 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "dtp.h"

void    serverPI(char *str, t_usr **usr, int cs);

int     s_logout(t_token **lst, t_usr **usr);
int     ft_list(t_token **lst, t_usr **usr);

int     user_reply(int code, char *msg, int cs);
int     check_user(t_usr **usr, int cs);
int     verify_auth(t_usr **usr, char *str);

/**
 * Authentificaton
 */
int     s_auth(t_token **lst, t_usr **usr);
int     pass(t_token **lst, t_usr **usr);
int     create(t_token **lst, t_usr **usr);
int     init_pass(t_token **lst, t_usr **usr);

/**
 * Directory
*/
int     cwd(t_token **lst, t_usr **usr);
int     s_pwd(t_token **lst, t_usr **usr);
int     complete_tab(char **exec, t_token **lst);
int     handle_file(char *file, t_usr **usr);
int     handle_dir(char *dir, t_usr **usr);
size_t     path_file(char *file);

/**
 * Server Data Transfer Protocol
 */
int     s_get(t_token **lst, t_usr **usr);
int     s_put(t_token **lst, t_usr **usr);
int     wait_client(int s, struct in_addr addr, int fd, int mode);
int     handle_client(int s, int fd, int mode);
int     send_info(int fd, int cs);
int     get_stream(int s, int fd, int print, off_t size);
int     put_stream(int s, int fd);
int     get_port(int s);
int     get_socket(t_usr *usr);
int     connect_socket(struct in_addr addr, int port);


#endif