/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 15:53:23 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/02 16:46:40 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int     send_file(int socket, char *file)
{
    int     r;
    int     fd;
    char    buf[1024];
    struct stat stat;
    
    if ((fd = open(file, O_RDONLY)) != -1)
    {
        if (!fstat(fd, &stat))
        {
            ft_putnbr(stat.st_size);
            send(socket, &stat.st_size, sizeof(int), 0);
            while ((r = read(fd, buf, 1023)) > 0)
            {
                ft_putnbr(r);
                ft_putendl("");
                buf[r] = '\0';
                ft_putendl(buf);
                send(socket, buf, r, 0);
            }
            close(fd);
            if ((r = recv(socket, buf, 1023, 0)) > 0)
            {
                buf[r] = '\0';
                if (!ft_strcmp("DONE", buf))
                    ft_putendl("END SEND FILE");
            }
            return (1);
        }
    }
    return (0);
}

int     recv_file(int socket, char  *file)
{
    int     r;
    int     fd;
    int     len;
    int     tot;
    char    buf[1024];

    tot = 0;
    if ((fd = open(file, O_APPEND | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
    {
        send(socket, "FILE CREATED", ft_strlen("FILE CREATED"), 0);
        recv(socket, &len, sizeof(int), 0);
        ft_putnbr(len);
        while ((tot != len) && ((r = recv(socket, buf, 1023, 0)) > 0))
        {
            buf[r] = '\0';
            ft_putendl(buf);
            ft_putstr("r = ");ft_putnbr(r);ft_putendl("");
            write(fd, buf, r);
            tot += r; // Use this data for progress bar with cmd_line
        }
        close(fd);
        send(socket, "DONE", 4, 0);
        ft_putendl("END RECV FILE");
        return (1);
    }
    return (0);
}

void    ft_lget(t_token **lst, int socket)
{
    (void)lst;
    int     r;
    char    buf[1024];
    t_token   *tmp;

    ft_putendl("IN GET CLIENT");
    if ((*lst)->next)
    {
        tmp = (*lst)->next;
        ft_putendl(tmp->str);
        send(socket, "get", 3, 0);
        if ((r = recv(socket, buf, 1023, 0)) > 0)
        {
            buf[r] = '\0';
            ft_putendl(buf);
            if (!ft_strcmp(buf, "IN"))
            {
                send(socket, tmp->str, ft_strlen(tmp->str), 0);
                if ((r = recv(socket, buf, 1023, 0)) > 0)
                {
                    buf[r] = '\0';
                    if (!ft_strcmp("EXIST", buf))
                        recv_file(socket, tmp->str);
                    else{
                        ft_putendl_fd("get: file does not exist", 2);
                    }
                }
            } else
                ft_putendl("WRONG");
        }
    }
}

int     ft_find(t_usr **usr, char *file)
{
    (void)usr;
    (void)file;

    return (1);
}
void    ft_get(t_token **lst, t_usr **usr)
{
    (void)lst;
    int     r;
    char    *str;
    char    buf[1024];
    t_usr   *tmp;

    ft_putendl("IN GET SERVER");
    if (*usr)
    {
        tmp = *usr;
        send(tmp->cs, "IN", 2, 0);
        if ((r = recv(tmp->cs, buf, 1023, 0)) > 0)
        {
            buf[r] = '\0';
            if (ft_find(usr, buf))
            { // file exist
                str = ft_strdup(buf);
                send(tmp->cs, "EXIST", 5, 0);
                if ((r = recv(tmp->cs, buf, 1023, 0)) > 0)
                {
                    buf[r] = '\0';
                    if (!ft_strcmp("FILE CREATED", buf))
                    {
                        if (send_file(tmp->cs, str))
                            ft_putendl("File send");
                        else {
                            send(tmp->cs, "NONE", 4, 0);
                            ft_putendl_fd("server: get: file does not exist", 2);
                        }
                    }
                }
            }
        }
    }
}