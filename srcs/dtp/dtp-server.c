/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp-server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 17:52:01 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/20 18:14:08 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtp.h"


int     wait_client(int s, struct in_addr addr)
{
    int     port;
    int     sock;

    send_code(s, 150)
    if ((port = get_port(s)))
    {
        if ((sock = connect_socket(addr, s)) > 0)
        {// demarrer transfert
            
        }
    }
    return (425); // Can't open data connection
}