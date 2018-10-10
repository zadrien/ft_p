/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userPI.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:06:05 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/09 12:41:53 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

typedef struct  s_pi
{
    char        *cmd;
    int        (*f)(t_token**, int s);
}               t_pi;

int     wait_response(int s, int res)
{
    int     r;

    recv(s, &res, sizeof(int), 0);
    printf("response:%d\n", r);
    if (res)
    {

    }
    return (r);
}

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

int    ft_username(t_token **lst, int s)
{
    (void)s;
    char                *line;
    char   buf[5] = "USER\0";

    line = ft_struct(buf, &(*lst)->next);
    send(s, line, ft_strlen(line), 0);
    ft_strdel(&line);
    return (wait_response(s, 0));

}

int    ft_password(t_token **lst, int s)
{
    (void)s;
    char                *line;
    char   buf[5] = "PASS\0";
    line = ft_struct(buf, &(*lst)->next);
    send(s, line, ft_strlen(line), 0);
    ft_strdel(&line);
    return (wait_response(s, 0));
}

int     ft_logout(t_token **lst, int s)
{
    (void)s;
    char                *line;
    char   buf[5] = "QUIT\0";
    line = ft_struct(buf, &(*lst)->next);
    send(s, line, ft_strlen(line), 0);
    ft_strdel(&line);
    return (wait_response(s, 0));
}

int     ft_pwd(t_token **lst, int s)
{
    (void)s;
    char                *line;
    char   buf[4] = "PWD\0";
    line = ft_struct(buf, &(*lst)->next);
    send(s, line, ft_strlen(line), 0);
    ft_strdel(&line);
    return (wait_response(s, 1));
}

int     userPI(char *str, int s)
{
    int                 i;
    int                 m;
    t_token             *lst;
    static const t_pi   cmd[3] = {{"username", &ft_username}, {"password", &ft_password}, {"logout", &ft_logout}};

    i = -1;
    m = 3;
    ft_putendl("ALLOR");
    if ((lst = parser(str)))
        while (++i < m)
        {
            if (!ft_strcmp(lst->str, cmd[i].cmd))
                return (cmd[i].f(&lst, s));
        }
    return (0);
}