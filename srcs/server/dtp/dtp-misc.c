/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp-misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 12:21:57 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 16:18:11 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int     get_stream(int s, int fd, int print, off_t size)
{
    (void)print;
    size_t  r;
    off_t   tot;
    char    buf[8];

    tot = 0;
    while ((r = recv(s, buf, 7, 0)))
    {
        buf[r] = '\0';
        write(fd, buf, ft_strlen(buf));
        tot += r;
    }
    close(s);
    if (tot == size)
        return (250);
    return (426);
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