/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverPI.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 12:48:21 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/10 11:11:33 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

typedef struct      s_cmd
{
    char            *cmd;
    int            (*f)(t_token**, t_usr**, int);
}                   t_cmd;


void    reply(int res, int cs)
{
    send(cs, &res, sizeof(int), 0);
}

int     ft_countarg(t_token **lst)
{
    int i;
    t_token *tmp;

    i = 0;
    if ((tmp = *lst))
        while (tmp)
        {
            i++;
            tmp = tmp->next;
        }
    return (i);
}

void    serverPI(char *str, t_usr **usr, int cs)
{
    int             i;
    int             m;
    t_token               *lst;
    static const t_cmd    cmd[4] = {{"USER", &ft_user}, {"PASS", &ft_password}, {"QUIT", &ft_logout}, {"LIST", &ft_list}};

    i = -1;
    m = 4;
    if ((lst = parser(str)))
        while (++i < m)
        {
            if (!ft_strcmp(lst->str, cmd[i].cmd))
                reply(cmd[i].f(&lst, usr, cs), cs);
        }

}