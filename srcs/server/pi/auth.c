/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 12:17:34 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/01 10:48:42 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int    co_attempt(t_usr **usr, char *name)
{
    DIR     *dir;
    char    *path;
    t_usr   *tmp;

    tmp = *usr;
    path = ft_strjoinf("./", name, 0);
    if ((dir = opendir(path)))
    {
        closedir(dir);
        ft_strdel(&path);
        tmp->user = ft_strdup(name);
        return (331);
    }
    ft_strdel(&path);
    return (332);
}

int     s_auth(t_token **lst, t_usr **usr)
{
    t_token *tmp;

    if (!(*usr)->user)
    {
        tmp = (*lst)->next;
        if (tmp)
        {
            if (ft_countarg(&tmp) == 1)
                return (co_attempt(usr, tmp->str));
        } else if ((*usr)->password) {
            return (230);
        }
    } else if (!(*usr)->password)
        return (331);
    return (332);
}

int     pass(t_token **lst, t_usr **usr)
{
    int     r;
    t_token *tmp;
    
    tmp = (*lst)->next;
    if (!(*usr)->user)
        return (530);
    if (!(*usr)->password)
    {
        if (ft_countarg(&tmp) == 1)
        {
            if ((r = verify_auth(usr, tmp->str)) == 1)
            {
                (*usr)->password = 1;
                return (230);
            } else
                return (r);
        } else
            return (501);
    }
    return (230);
}

int     s_logout(t_token **lst, t_usr **usr)
{
    char    *line;
    t_usr   *tmp;

    (void)lst;
    tmp = *usr;
    if (tmp->password)
    {
        tmp->password = 0;
        ft_strdel(&(tmp)->user);
        ft_strdel(&(tmp)->pwd);
        line = ft_strjoinf(tmp->home, "/", 0);
        line = ft_strjoinf(line, "..", 1);
        ft_strdel(&tmp->home);
        if (!chdir(line))
        {
            ft_strdel(&line);
            return (220);
        } else {
            close(tmp->cs);
            exit(EXIT_FAILURE);
        }
    }
    return (0);
} // to develop // find a way to return to root directory