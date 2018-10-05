/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverPI.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 12:48:21 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/05 16:54:48 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

typedef struct      s_cmd
{
    char            *cmd;
    int            (*f)(t_token**, int);
}                   t_cmd;


void    reply(int res, int cs)
{
    send(cs, &res, sizeof(int), 0);
}

int     ft_user(t_token **lst, int cs)
{
    (void)lst;
    (void)cs;
    ft_putendl("here");
    return (0);
}

int     ft_password(t_token **lst, int cs)
{
    (void)lst;
    (void)cs;
    return (0);
}

void    serverPI(char *str, int cs)
{
    int             i;
    int             m;
    t_token               *lst;
    static const t_cmd    cmd[2] = {{"USER", &ft_user}, {"PASS", &ft_password}};

    i = -1;
    m = 2;
    if ((lst = parser(str)))
        while (++i < m)
        {
            if (!ft_strcmp(lst->str, cmd[i].cmd))
                reply(cmd[i].f(&lst, cs), cs);
        }

}