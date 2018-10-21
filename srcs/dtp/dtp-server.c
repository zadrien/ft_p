/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp-server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 17:52:01 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/21 15:38:53 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtp.h"


int     handle_client(int s, int fd, int mode)
{
    int     r;

    r = -1;
    if (mode == GET)
    { // stocker dans un fichier
        r = get_stream(s, fd, NONE);
    } else {
        r = put_stream(s, fd);
    }
    return (r);
}

int     wait_client(int s, struct in_addr addr, int fd, int mode)
{
    int     port;
    int     sock;

    if ((port = get_port(s)))
    {
        printf("DTP PORT = %d\n", port);
        if ((sock = connect_socket(addr, port)) > 0)
        {// demarrer transfert
            handle_client(sock, fd, mode);
            // send_code(s, 226);
            ft_putendl("close socket");
            close(sock);
            return (226);
        }
    }
    return (425); // Can't open data connection
}