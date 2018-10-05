/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userPI.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:06:05 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/05 13:59:47 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

typedef struct  s_pi
{
    char        *cmd;
    void        (*f)(t_token**, int s);
}               t_pi;

char    *ft_struct(char *cmd, t_token **arg)
{
    char    *line;
    t_token *tmp;

    line = ft_strdup(cmd);
    if ((tmp = *arg))
    {
        line = ft_strjoinf(line, " ", 1);
        while (tmp)
        {
            line = ft_strjoinf(line, tmp->str, 1);
            if (tmp->next)
                line = ft_strjoinf(line, " ", 1);
            tmp = tmp->next;
        }
    }
    ft_putendl(line);
    return (line);
}

void    ft_username(t_token **lst, int s)
{
    (void)s;
    char                *line;
    char   buf[4] = "USER";

    line = ft_struct(buf, &(*lst)->next);
    ft_putendl(line);

}

void    ft_password(t_token **lst, int s)
{
    (void)s;
    char                *line;
    char   buf[4] = "PASS";
    line = ft_struct(buf, &(*lst)->next);
    ft_putendl(line);
}

int     userPI(char *str, int s)
{
    int                 i;
    int                 m;
    t_token             *lst;
    static const t_pi   cmd[2] = {{"username", &ft_username}, {"password", &ft_password}};

    i = -1;
    m = 2;
    ft_putendl("ALLOR");
    if ((lst = parser(str)))
        while (++i < m)
        {
            if (!ft_strcmp(lst->str, cmd[i].cmd))
                cmd[i].f(&lst, s);
        }
    return (0);
}