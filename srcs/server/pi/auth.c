/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 12:17:34 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/09 12:18:04 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int     ft_user(t_token **lst, t_usr **usr, int cs)
{
    (void)cs;
    (void)usr;
    ft_putendl("hereeee");
    int     r;
    t_token *tmp;
    t_usr *tmp2;
    
    if (*usr)
        return (check_user(usr, cs));
    if (ft_countarg(&(*lst)->next) == 1)
    {
        ft_putendl("PASS");
        tmp = (*lst)->next;
        char *str = ft_strjoinf("./usr/", tmp->str, 0);
        ft_putendl(str);
        if ((r = chdir(str)) != -1)
        {
            if (!(*usr = (t_usr*)malloc(sizeof(t_usr))))
                return (0);
            tmp2 = *usr;
            tmp2->cs = cs;
            tmp2->user = ft_strdup(tmp->str);
            tmp2->password = 0;
            tmp2->pwd = getcwd(NULL, 1023);
            tmp2->next = NULL;
            ft_putnbr(r);
            ft_putendl("directory changed");
            return (331);
        } else {
            ft_putendl("error");
        }
    }
    return (0);
}

int     ft_password(t_token **lst, t_usr **usr, int cs)
{
    (void)lst;
    (void)cs;
    (void)usr;
    t_usr   *tmp;
    t_token *l;

    if (check_user(usr, cs) == 331)
    {
        tmp = *usr;
        if (!tmp->password)
        {
            if (ft_countarg(&(*lst)->next))
            {
                l = (*lst)->next;
                if (verify_auth(l->str))
                {
                    tmp->password = 1;
                    return (check_user(usr, cs));
                }
            }
        }
    }
    return (0);
}

int     ft_logout(t_token **lst, t_usr **usr, int cs)
{
    (void)lst;
    (void)cs;
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