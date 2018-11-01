/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userPI.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:06:05 by zadrien           #+#    #+#             */
/*   Updated: 2018/11/01 10:32:14 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

typedef struct  s_pi
{
    char        *cmd;
    int        (*f)(t_token**, int s);
}               t_pi;

int    ft_password(t_token **lst, int s)
{
    if ((*lst)->next)
        return (send_pass(s, (*lst)->next->str));
    return (0);
}

int     ft_logout(t_token **lst, int s)
{
    int     r;
    char    buf[5] = "QUIT\0";

    if (send_cmd(buf, &(*lst)->next, s))
    {
        if ((r = get_code(s)) == 220)
        {
            print_msg("Logout successful", GREEN, 2);
            return(1);
        }
    }
    return (0);
}

int     ft_ls(t_token **lst, int s)
{
    int     r;
    char    buf[5] = "LIST\0";

    if (send_cmd(buf, &(*lst)->next, s))
    {
        if ((r = wait_server(s, NONE, PRINT, GET)) == 226)
            return (1);
        
    }
    return (0);
}

int     ft_acct(t_token **lst, int s)
{
    char    buf[5] = "ACCT\0";

    if (send_cmd(buf, &(*lst)->next, s))
        return (get_code(s));
    return (0);
}

int     quit_client(t_token **lst, int s)
{
    (void)lst;
    free_token(lst);
    // verifier que des transfert ne sont pas en cours
    close(s);
    print_msg("Connexion with server closed\nBye.", RED, 2);
    return (-1);
}

int     userPI(char *str, int s)
{
    int                 i;
    int                 m;
    t_token             *lst;
    static const t_pi   cmd[13] = {{"username", &auth}, {"password", &ft_password}, {"init", &create_pass}, {"logout", &ft_logout},
                                    {"ls", &ft_ls}, {"account", &ft_acct}, {"lls", &ft_lls}, {"lpwd", &ft_lpwd}, {"pwd", &ft_pwd},
                                    {"lcd", &ft_lcd}, {"cd", &ft_cwd}, {"get", &c_get}, {"put", &c_put}};

    i = -1;
    m = 13;
    if ((lst = parser(str)))
        if (lst->str)
        {
            while (++i < m)
            {
                if (!ft_strcmp(lst->str, cmd[i].cmd))
                    return (cmd[i].f(&lst, s));
            }
            if (i == m && !ft_strcmp(lst->str, "quit"))
                return (quit_client(&lst, s)); // clear all var
        }
    free_token(&lst);
    return (0);
}