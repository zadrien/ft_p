/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:32:36 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/30 18:19:51 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DTP_H
# define DTP_H

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
int     get_stream(int s, int fd, int print, off_t size);
int     put_stream(int s, int fd);
int     handle_stream(int s, int fd, int print, int mode);
int     wait_server(int s, int fd, int print, int mode);

/**
 * SERVER-DTP
*/
int     handle_client(int s, int fd, int mode);
int     wait_client(int s, struct in_addr addr, int fd, int mode);

#endif