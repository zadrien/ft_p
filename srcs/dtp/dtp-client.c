/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp-client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 17:51:53 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/20 18:30:12 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtp.h"

int wait_server(int s, int fd, int print, int mode)
{
    int     port;
    int     sock;

    port = 50042;
    if (get_code(s) == 150)
    {
        send_code(s, port);
        if ((sock = listen_socket(port)))
        {
            if ((cs = accept_socket(sock)))
            { // begin transfer
                handle_stream(cs, fd, print, mode);
            }
        }
    }
}