/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:58:31 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/02 13:05:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void ft_cmd(t_token **cmd, t_usr **usr)
{
    (void)usr;
    (void)cmd;
    ft_putendl_fd("cmd search", 2);
}

void ft_cd(t_token **arg, t_usr **usr)
{
    (void)usr;
    (void)arg;
    ft_putendl_fd("cd", 2);

}

void    ft_env(t_token **arg, t_usr **usr)
{
    t_usr *tmp;
    (void)arg;
    if (*usr)
    {
        tmp = *usr;
        ft_putstr("cs: ");
        ft_putnbr(tmp->cs);
        ft_putendl("");
        ft_putstr("username: ");
        ft_putendl(tmp->user);
        ft_putstr("pwd: ");
        ft_putendl(tmp->pwd ? tmp->pwd : "");
    }
}

void    execution(char *str, t_usr **usr)
{
    int                     i;
    t_token                 *tok;
    t_token                 *tmp;
    static const t_builtin  cmd[4] = {{"cd", &ft_cd}, {"get", &ft_get}, {"put", &ft_put}, {"env", &ft_env}};

    i = -1;
    tok = parser(str);
    if (tok) {
        tmp = tok;
        ft_putendl(tmp->str);
        ft_putendl("HERE");
        while (++i < 4)
        {
            ft_putnbr(i);
            if (!ft_strcmp(cmd[i].cmd, tmp->str))
            {
                ft_putnbr(i);
                return (cmd[i].f(&tmp, usr));
            }
        }
        return (ft_cmd(&tmp, usr));
        while (tmp) {
            ft_putendl(tmp->str);
            tmp = tmp->next;
        }
    } else {
        ft_putendl_fd("token is null", 2);
    }
}