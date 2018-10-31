/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 12:17:34 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 11:44:51 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int    co_attempt(t_usr **usr, char *name)
{
    DIR     *dir;
    char    *path;
    t_usr   *tmp;

    tmp = *usr;
    path = ft_strjoinf("./usr/", name, 0);
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
    } else
        return (331);
    return (332);
}

int     pass(t_token **lst, t_usr **usr)
{
    int     r;
    t_token *tmp;
    
    tmp = (*lst)->next;
    if (tmp)
    {
        if ((*usr)->user && !(*usr)->password)
        {
            if (ft_countarg(&tmp) == 1)
            {
                if ((r = verify_auth(usr, tmp->str)) == 1)
                {
                    (*usr)->password = 1;
                    return (230);
                } else if (r == 650)
                    return (650);
            }
        } else if ((*usr)->user && (*usr)->password) {
            return (230); // voir cas si les deux sont nul donc condition vrai
        }
    }
    return (530);
}

int     s_logout(t_token **lst, t_usr **usr)
{
    (void)lst;
    ft_putendl("LOGOUT");

    t_usr   *tmp;
    if ((tmp = *usr))
    {
        ft_strdel(&(tmp)->user);
        ft_strdel(&(tmp)->pwd);
        free(tmp);
        *usr = NULL;
        return (1);
    }
    return (0);
} // to develop // find a way to return to root directory