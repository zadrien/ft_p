/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 10:49:12 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/22 17:53:44 by zadrien          ###   ########.fr       */
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

int     verify_auth(t_usr **usr, char *str)
{
    int     fd;
    char    *line;
    char    *path;
    char    *file;
    t_usr   *tmp;
    

    tmp = *usr;
    path = NULL;
    path = ft_strjoinf("./usr/", tmp->user, 0);
    file = ft_strjoinf(path, "/auth", 0);
    if ((fd = open(file, O_RDONLY)) > 0)
    {
        ft_strdel(&file);
        if (get_next_line(fd, &line) > 0)
        {
            if (!ft_strcmp(str, line))
            {
                ft_strdel(&line);
                close(fd);
                if (chdir(path) != -1)
                {
                    ft_strdel(&path);
                    tmp->pwd = getcwd(NULL, 1023);
                    return (1);
                }
            } else
                close(fd);
        }
    } else {
        ft_strdel(&path);
        return (650);
    }
    ft_strdel(&path);
    return (0);
}