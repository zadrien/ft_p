/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 10:49:12 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/09 12:18:34 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int     user_reply(int code, char *msg, int cs)
{
    (void)cs;
    ft_putendl_fd(msg, 2);
    return (code);
}

int     check_user(t_usr **usr, int cs)
{
    t_usr   *tmp;
    if ((tmp = *usr))
    {
        if (tmp->user)
        {
            if (tmp->password)
            {
                return (user_reply(230, "User logged in, proceed", cs));
            } else {
                return (user_reply(331, "User name okay, need password", cs));
            }
        } else {
            return (user_reply(332, "Need account for login", cs));
        }
    } else {
        return (user_reply(332, "Need account for login", cs));
    }
}

int     verify_auth(char *str)
{
    int     fd;
    char    *line;

    if ((fd = open("auth", O_RDONLY)))
    {
        if (get_next_line(fd, &line) > 0)
        {
            ft_putendl(line);
            if (!ft_strcmp(str, line))
            {
                ft_strdel(&line);
                close(fd);
                return (1);
            }
            close(fd);
        }
    }
    return (0);
}