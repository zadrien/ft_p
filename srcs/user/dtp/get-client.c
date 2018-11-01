/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get-client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 11:57:36 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 15:51:55 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int     get_error(int code, int fd)
{
    if (code == 550)
    {
        ft_putstr_fd(RED, 2);
        ft_putendl_fd("get: error: file not found", 2);
    } else if (code == 425) {
        ft_putendl_fd("get: error: can't open data connection", 2);
    } else if (code == 226) {
        ft_putstr_fd(YELLOW, 2);
        ft_putendl_fd("Closing data connection..", 2);
        ft_putstr_fd(RESET, 2);
        return (1);
    }
    ft_putstr_fd(RESET, 2);
    if (fd != -1)
        close(fd);
    return (0);
}

int     c_get(t_token **lst, int s)
{
    int     r;
    int     fd;
    char    *line;
    char    buf[5] = "RETR\0";
    t_token *tmp;
    
    tmp = (*lst)->next;
    if (ft_countarg(&tmp) == 1)
    {
        line = ft_struct(buf, &tmp);
        send(s, line, ft_strlen(line), 0);
        if ((r = get_code(s)) == 150)
        {
            if ((fd = open(tmp->str, O_APPEND | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
            {
                ft_putendl_fd("Transfering file from server..", 2);
                ft_putstr_fd("File name: ", 2);
                ft_putendl_fd(tmp->str, 2);
                ft_strdel(&line);
                r = wait_server(s, fd, NONE, GET);
                return (get_error(r, fd));
            }
        }
    } // verify path too
    return (get_error(r, -1));
}