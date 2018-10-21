/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream-handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 12:21:57 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/21 15:59:08 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dtp.h"

int     get_stream(int s, int fd, int print)
{
    int     r;
    char    buf[8];

    while ((r = recv(s, buf, 7, 0)))
    {
        buf[r] = '\0';
        if (print)
            ft_putstr(buf);
        else
            write(fd, buf, ft_strlen(buf));
    }
    if (!print)
        close(fd);
    close(s);
    ft_putendl("END GET STREAM");
    return (226);
}

int     put_stream(int s, int fd)
{
    int     r;
    char    buf[8];

    while ((r = read(fd, buf, 7)) > 0)
    {
        ft_putendl("HERE");
        buf[r] = '\0';
        send(s, buf, ft_strlen(buf), 0);
    }
    perror("read()");
    close(fd);
    close(s);
    ft_putendl("END PUT STREAM");
    return (226);
}