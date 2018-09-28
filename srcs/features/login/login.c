/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   login.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:22:22 by zadrien           #+#    #+#             */
/*   Updated: 2018/09/28 14:08:59 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void    fork_client(t_usr **usr)
{
    int     r;
    char    str[1024];
    t_usr  *tmp;
    tmp = *usr;
    // if (fork() == 0)
    // {
        ft_putendl("In the fork client");
        while ((r = read(tmp->cs, str, 1023)) > 0)
        {
            str[r] = '\0';
            ft_putendl(str);
            execution(str, &tmp);
            // ft_bzero(str, 1024);
            send_msg(tmp->cs, "success");
        }
        ft_putendl("no more read");
        // exit(0);
    // }    
}

void     finding_usr(t_usr **lst, int cs)
{
    int     r;
    char    str[1024];
    t_usr   *tmp;

    if (fork() == 0)
    {
        while((r = read(cs, str, 1024)) > 0)
        {
            str[r] = '\0';
            if ((tmp = check_user(lst, str)))
            {
                tmp->cs = cs;
                ft_putnbr(tmp->cs);
                ft_putendl("");
                ft_putendl("user found");
                send_msg(cs, "SUCCESS");
                fork_client(&tmp);
            } else {
                send_msg(cs, "ERROR");
                close(cs);
            }
        }
        ft_putendl("END FORK");
        // exit(0);
        kill(getpid(), 9);
    } else {

    }
}

t_usr      *check_user(t_usr **lst, char *name)
{
    t_usr   *tmp;

    if (*lst)
    {
        ft_putendl("Pass here");
        tmp = *lst;
        while (tmp)
        {
            if (!ft_strcmp(tmp->user, name))
                return tmp;
        }
    } else {
        ft_putendl("Create new node");
        if (!(tmp = (t_usr*)malloc(sizeof(t_usr))))
            return NULL;
        tmp->user = ft_strdup(name);
        tmp->pwd = ft_strdup("/");
        tmp->next = NULL;
        *lst = tmp;
        return (tmp);
    }
    return (NULL);
}