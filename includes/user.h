/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:17:40 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 16:15:52 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_H
# define USER_H

# include "ftp.h"

void    start_line(t_edit *term, int socket, int printable, char *prompt);

char    *ft_struct(char *cmd, t_token **arg);
int     userPI(char *str, int s);
int     com_link(char *addr, char *port);
int     ft_lls(t_token **lst, int socket);
int     wait_response(int s, int res);
/**
 * Authentification
*/
int     auth(t_token **lst, int s);
int     create_user(int s, char *name);
int     create_password(int s, char *pass);
int     create_pass(t_token **lst, int s);


/**
 * Directory
*/
int     ft_lpwd(t_token **lst, int socket);
int    ft_pwd(t_token **lst, int s);
int     ft_lcd(t_token **lst, int socket);
int     ft_cwd(t_token **lst, int s);

/**
 * Client Data Transfer Protocol 
 */
int     c_get(t_token **lst, int s);
int     c_put(t_token **lst, int s);
int     wait_server(int s, int fd, int print, int mode);
int     handle_stream(int s, int fd, int print, int mode);
int     put_file(int s, int fd, off_t size);
int     get_file(int s, int fd, int print, off_t size);
int     get_info(int s);
void    print_progress(off_t tot, off_t size);
int     replace_curs(off_t tot, off_t size);
void    progress_bar(void);
int     listen_socket(int port);
int     accept_socket(int sock);
int     get_error(int code, int fd);

#endif