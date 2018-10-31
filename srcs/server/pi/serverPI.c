/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverPI.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 12:48:21 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/31 11:45:07 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

typedef struct      s_cmd
{
    char            *cmd;
    int            (*f)(t_token**, t_usr**);
}                   t_cmd;


void    reply(int res, int cs)
{
    printf("Code send to client:%d\n", res);
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

int     ft_acct(t_token **lst, t_usr **usr)
{
    (void)*lst;
    t_usr   *tmp;
    char    str[INET_ADDRSTRLEN];

    if (*usr)
    {
        tmp = *usr;
        ft_putstr("Client socket: ");ft_putnbr(tmp->cs);ft_putendl("");
        inet_ntop(AF_INET, &tmp->addr, str, INET_ADDRSTRLEN);
        ft_putstr("Client IP: ");ft_putendl(str);
        ft_putstr("Client account: ");ft_putendl(tmp->user);
        ft_putstr("Password valid: ");ft_putnbr(tmp->password);ft_putendl("");
        ft_putstr("root: ");ft_putendl(tmp->home);
        ft_putstr("cwd: ");ft_putendl(tmp->pwd);
    }
    return (1);
}

void    serverPI(char *str, t_usr **usr, int cs)
{
    int                 i;
    int                 m;
    t_token             *lst;
    static const t_cmd  cmd[11] = {{"USER", &s_auth}, {"PASS", &pass}, {"CREAT", &create}, {"INIT", &init_pass}, {"QUIT", &s_logout},
                                    {"LIST", &ft_list}, {"ACCT", ft_acct}, {"RETR", &s_get}, {"STOU", &s_put}, {"CWD", &cwd},
                                    {"PWD", &s_pwd}};

    i = -1;
    m = 11;
    ft_putendl(str);
    if ((lst = parser(str)))
        while (++i < m)
        {
            if (!ft_strcmp(lst->str, cmd[i].cmd))
            {
                reply(cmd[i].f(&lst, usr), cs);
                return (free_token(&lst));
            }
        }
    free_token(&lst);
    reply(500, cs);
// suppression list chaine
}