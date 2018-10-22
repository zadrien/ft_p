/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth_creat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:12:06 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/22 17:55:07 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int     create_repo(t_usr **usr, char *dir)
{
    char    *line;

    line = ft_strjoinf("./usr/", dir, 0);
    if (!mkdir(line, 0777)) {
        ft_strdel(&line);
        (*usr)->user = ft_strdup(dir);
        return (1); // repo created
    } else {
        ft_putendl_fd("Error while creating repo", 2);
    }
    ft_strdel(&line);
    return (331); // Already exist
}

int     init_pass(t_token **lst, t_usr **usr)
{
    int     fd;
    char    *path;
    char    *file;
    t_token *tmp;

    tmp = (*lst)->next;
    if (tmp && tmp->str)
    {
        if ((*usr)->user)
        {
            path = ft_strjoinf("./usr/", (*usr)->user, 0);
            file = ft_strjoinf(path, "/auth", 0);
            if ((fd = open(file, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) > 0)
            {
                ft_strdel(&file);
                write(fd, tmp->str, ft_strlen(tmp->str));
                close(fd);
                if (!chdir(path))
                {
                    (*usr)->password = 1;
                    (*usr)->pwd = getcwd(NULL, 1023);
                    return (230);
                }
            }
        } else {
            return (332);
        }
    }
    return (0);
}

int     create(t_token **lst, t_usr **usr)
{
    t_token *tmp;

    tmp = (*lst)->next;
    if (!(*usr)->user && !(*usr)->password)
        if (tmp)
        {
            if (ft_countarg(&tmp) == 1)
                return (create_repo(usr, tmp->str));
        }
    return (0);
}