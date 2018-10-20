/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 11:44:41 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/20 10:51:41 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

int     com_link(char *addr, char *port)
{
    int                 p;
    int                 sock;
    int                 optval = 1;
    struct protoent     *proto;
    struct sockaddr_in  sin;

    p = ft_atoi(port);
    if ((proto = getprotobyname("tcp")))
    {
        if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) != -1)
        {
            if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
                ft_putendl_fd("ERROR SERSOCKOPT", 2);
            sin.sin_family = AF_INET;
            sin.sin_port = htons(p);
            sin.sin_addr.s_addr = inet_addr(addr);
            if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
            {
                ft_putendl_fd("Connect error", 2);
                return (-1);
            }
            return (sock);
        } else {
            ft_putendl_fd("socket creation error", 2);
        }
    } else {
        ft_putendl_fd("proto is null", 2);
    }
    return (-1);
}