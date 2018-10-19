/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 12:17:34 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/19 10:31:44 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int    co_attempt(t_usr **usr, char *name)
{
    char    *str;
    t_usr   *tmp;

    tmp = *usr;
    str = ft_strjoinf("./usr/", name, 0);
    ft_putendl(str);
    if (chdir(str) != -1)
    {
        tmp->user = ft_strdup(name);
        tmp->pwd = getcwd(NULL, 1023);
        ft_putendl_fd("Directory changed", 2);
        ft_putendl_fd("User name okay, need password", 2);
        return (331);
    }
    ft_putendl_fd("Directory doesn't exist", 2);
    return (332);
}

int     ft_usr(t_token **lst, t_usr **usr)
{
    t_usr   *tmp;

    if ((tmp = *usr))
    {
        if (!tmp->user)
        {
            if ((ft_countarg(&(*lst)->next)) == 1)
            {
                return (co_attempt(usr, (*lst)->next->str));
            }
        } else if (tmp->password == 1) {
            return (230);
        } else {
            ft_putendl_fd("User name okay, need password", 2);
            return (331);
        }
    }
    ft_putendl_fd("t_usr struct null", 2);
    return (-2); // to change
}

int     ft_pass(t_token **lst, t_usr **usr)
{
    t_usr   *tmp;

    if ((tmp = *usr))
    {
        if (tmp->user && !tmp->password)
        {
            if (ft_countarg(&(*lst)->next) == 1)
            {
                if (verify_auth((*lst)->next->str))
                {
                    tmp->password = 1;
                    return (230);
                }
            }
        }
    }
    return (530);
}

int     ft_logout(t_token **lst, t_usr **usr)
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
} // to develop