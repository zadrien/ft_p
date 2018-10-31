/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp-client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:59:26 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 16:45:36 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int     get_file(int s, int fd, int print, off_t size)
{
    off_t   tot;
    size_t  r;
    char    buf[8];

    tot = 0;
    if (!print)
        progress_bar();
    while ((r = recv(s, buf, 7, 0)))
    {
        buf[r] = '\0';
        if (print)
            ft_putstr(buf);
        else {
            write(fd, buf, ft_strlen(buf));
            tot += r;
            print_progress(tot, size);
        }
    }
    if (!print)
    {
        close(fd);
        return (replace_curs(tot, size));
    }
    close(s);
    return (226);
}

int     put_file(int s, int fd, off_t size)
{
    off_t   tot;
    size_t  r;
    char    buf[8];

    tot = 0;
    progress_bar();
    while ((r = read(fd, buf, 7)) > 0)
    {
        buf[r] = '\0';
        send(s, buf, ft_strlen(buf), 0);
        tot += r;
        print_progress(tot, size);
    }
    close(fd);
    close(s);
    return (replace_curs(tot, size));
}

int     handle_stream(int s, int fd, int print, int mode)
{
    int         r;
    off_t       size;
    struct stat buf;

    r = 0;
    if (mode == GET)
    {
        if (!print)
            size = get_info(s);
        r = get_file(s, fd, print, size);
    } else {
        // envoyer au serveur
        ft_putendl("MODE PUT");
        printf("%d\n", fd);
        if (!fstat(fd, &buf))
            r = put_file(s, fd, buf.st_size);
        else {
            close(s);
            close(fd);
            return (451);
        }
    }
    return (r);
}

int     wait_server(int s, int fd, int print, int mode)
{
    int     cs;
    int     port;
    int     sock;
    socklen_t           len;
    struct sockaddr     addr;

    port = 50042;
    // if ((r = get_code(s)) == 150) // can cause bug
    // {
        send_code(s, port);
        if ((sock = listen_socket(port)) > 0)
        {
            if ((cs = accept(sock, &addr, &len)) > 0)
            {
                handle_stream(cs, fd, print, mode);
                close(sock);
                return (get_code(s));
            }
            close(sock);
        }
    // }
    return (425);
}