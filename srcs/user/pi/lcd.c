/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:32:14 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 11:46:50 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void    change_in_env(t_env **env, char *cwd)
{
    t_env *tmp;
    if (*env)
    {
        if ((tmp = find_node(env, "PWD", NULL)))
        {
            ft_strdel(&tmp->value);
            tmp->value = ft_strdup(cwd);
        }
    }
} // useless

int    ft_lcd(t_token **lst, int socket)
{
    (void)socket;
    int     i;
    char    buf[1024];
    t_token *tmp;

    if ((i = ft_countarg(&(*lst)->next)) <= 1)
    {
        tmp = (*lst)->next;
        ft_putendl(tmp->str);
        ft_putendl_fd("lcd", 2);
        if (!chdir(tmp->str))
        {
            getcwd(buf, 1023);
            return (1);
        }
    } else {
        ft_putendl_fd("cd: too many arguments", 2);
    }
    return (0);
}
