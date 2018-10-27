/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userPI.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:06:05 by zadrien           #+#    #+#             */
/*   Updated: 2018/10/27 12:22:25 by zadrien          ###   ########.fr       */
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
    // char    buf[8];

    if (res)
    {
        return (recept(s, NONE, PRINT));
        // while (read(s, buf, 7) > 0)
        // {
        //     buf[r] = '\0';
        //     ft_putendl(line);
        //     ft_strdel(&line);
        // }
    } else {
        recv(s, &r, sizeof(int), 0);
        printf("response:%d\n", r);
    }
    return (r);
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
    int    r;
    char                *line;
    char   buf[5] = "PASS\0";
    line = ft_struct(buf, &(*lst)->next);
    send(s, line, ft_strlen(line), 0);
    ft_strdel(&line);
    r = get_code(s);
    if (r == 230) {
        return (1);
    } else if (r == 650) {
        ft_putendl_fd("Please use init command", 2);
    }
    return (0);
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

int     ft_ls(t_token **lst, int s)
{
    (void)s;
    char    *line;
    char    buf[5] = "LIST\0";
    line = ft_struct(buf, &(*lst)->next);
    send(s, line, ft_strlen(line), 0);
    ft_strdel(&line);
    return (wait_response(s, 1));
}

int     ft_acct(t_token **lst, int s)
{
    (void)lst;
    char    *line;
    char    buf[5] = "ACCT\0";

    line = ft_struct(buf, &(*lst)->next);
    send(s, line, ft_strlen(line), 0);
    ft_strdel(&line);
    return (wait_response(s, 0));
}

int     quit_client(char **str, t_token **lst, int s)
{
    (void)lst;
    // verifier que des transfert ne sont pas en cours
      ft_strdel(str);
    // free_lst_token(lst);
    close(s);
    ft_putendl("quit client");
    exit(EXIT_SUCCESS);
}

int     userPI(char *str, int s)
{
    int                 i;
    int                 m;
    t_token             *lst;
    static const t_pi   cmd[11] = {{"username", &auth}, {"password", &ft_password}, {"init", &create_pass}, {"logout", &ft_logout},
                                    {"ls", &ft_ls}, {"account", &ft_acct}, {"lls", &ft_lls}, {"lpwd", &ft_lpwd},
                                    {"lcd", &ft_lcd}, {"get", &c_get}, {"put", &c_put}};

    i = 0;
    m = 11;
    ft_putendl("ALLOR");
    ft_putendl(str);
    if ((lst = parser(str)))
    {
        ft_putendl(lst->str);
        while (++i < m)
        {
            ft_putendl("HI");
            if (!ft_strcmp(lst->str, cmd[i].cmd))
                return (cmd[i].f(&lst, s));
            i++;
            if (i == m && !ft_strcmp(lst->str, "quit"))
                quit_client(&str, &lst, s);
        }
    }
    return (0);
}